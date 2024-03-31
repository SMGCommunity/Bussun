import setup, os, sys, subprocess
from pathlib import Path
from glob import glob
from enum import StrEnum

class Region(StrEnum):
    USA = "E"
    PAL = "P"
    JPN = "J"
    KOR = "K"

def deleteDFiles():
    dirs = os.listdir(os.getcwd())

    for dire in dirs:
        if dire.endswith(".d"):
            os.remove(os.path.join(os.getcwd(), dire))

def main():
    flags = "-c -Cpp_exceptions off -nodefaults -proc gekko -fp hard -lang=c++ -O4,s -inline on -rtti off -sdata 0 -sdata2 0 -align powerpc -func_align 4 -str pool -enum int -DGEKKO -DMTX_USE_PS "

    for build_flag in [x for x in sys.argv if x.startswith("-D")]:
        flag = build_flag[2:]
        print(f"Bulding with flag {flag} true")
        flags += f"{build_flag} "

    allowed = [entry.name for entry in Region]

    region_arg = next((x for x in sys.argv if x in allowed), "USA")

    flags += f"-D{region_arg} "

    region = Region[region_arg]

    symbol_map = f"Symbols\\RMG{region}01.map"

    includes = "-i . -I- -i Petari\\include -I- -i source -I- -i include "
    default_compiler_path = Path("Wii\\1.3")
    rvl_sdk_path = Path("Petari\\libs\\RVL_SDK\\include")
    trk_path = Path("Petari\\libs\\MetroTRK\\include")
    runtime_path = Path("Petari\\libs\\Runtime\\include")
    msl_c_path = Path("Petari\\libs\\MSL_C\\include")
    facelib_path = Path("Petari\\libs\\RVLFaceLib\\include")
    jsystem_path = Path("Petari\\libs\\JSystem\\include")
    nw4r_path = Path("Petari\\libs\\nw4r\\include")
    includes += f"-i {facelib_path} -i {rvl_sdk_path} -I- -i {trk_path} -I- -i {runtime_path} -I- -i {msl_c_path} -I- -i {jsystem_path} -I- -i {nw4r_path} "
    flags += includes
    compiler_path = Path(f"Compilers\\{default_compiler_path}\\mwcceppc.exe")
    kamek_path = Path("Kamek\\Kamek.exe")
    tasks = list[tuple[str, str]]()
    files = [x for x in glob("source/*.cpp")]
    files += [x for x in glob("source/*.c")]
    for file in files:
        source_path = file
        if file.endswith(".cpp"):
            build_path = source_path.replace(".cpp", ".o")
        elif file.endswith(".c"):
            build_path = source_path.replace(".c", ".o")
        tasks.append((source_path, build_path))
    for (source_path, build_path) in tasks:
        print(f"Compiling {source_path}..")
        if subprocess.call(f"{compiler_path} {flags} {source_path} -o {build_path}", shell=True) == 1:
            deleteDFiles()
            sys.exit(1)
    objects = ' '.join([x for (_, x) in tasks])
    flags = f"-static=0x80001800 -output-riiv=build{region}.xml -externals={symbol_map}"
    if subprocess.call(f"{kamek_path} {objects} {flags}") != 0:
        sys.exit(1)
    for (_, obj) in tasks:
        os.remove(obj)
    print("Compilation complete.")

if __name__ == "__main__":
    if not os.path.exists("Kamek") and not os.path.exists("Compilers"):
        setup.setup()
    main()