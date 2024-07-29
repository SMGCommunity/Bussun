import os
import shutil
import subprocess
import sys
from pathlib import Path


def err(message: str):
    print(f"Error: {message}")
    sys.exit(1)


def dep(path, name):
    path = Path(path)
    if not os.path.exists(path):
        err(f"{name} not found!")
    return path


def prepare_bin():
    if os.path.exists("bin"):
        shutil.rmtree("bin")
    os.makedirs("bin")


REGIONS = ["PAL", "USA", "JPN", "TWN", "KOR"]
LETTERS = ['P', 'E', 'J', 'W', 'K']

MWCCEPPC = dep("deps/CodeWarrior/mwcceppc.exe", "CodeWarrior compiler")
KAMEK = dep("deps/Kamek/Kamek.exe", "Kamek linker")
SYMBOLS = dep("symbols", "Symbols folder")

def getregionletter(region: str):
    for i in range(0, len(REGIONS)):
        reg = REGIONS[i]
        if region == reg:
            return LETTERS[i]

def build(region: str, outputPath: str, buildFullXML: bool):
    rvl_sdk_path = "Petari/libs/RVL_SDK/include"
    trk_path = "Petari/libs/MetroTRK/include"
    runtime_path = "Petari/libs/Runtime/include"
    msl_c_path = "Petari/libs/MSL_C/include"
    facelib_path = "Petari/libs/RVLFaceLib/include"
    jsystem_path = "Petari/libs/JSystem/include"
    nw4r_path = "Petari/libs/nw4r/include"
#    compile_cmd = f"{MWCCEPPC} -c -Cpp_exceptions off -nodefaults -proc gekko -fp hard -lang=c++ -O4,s -inline on " \
#                  f"-rtti off -sdata 0 -sdata2 0 -align powerpc -func_align 4 -str pool -enum int -DGEKKO " \
#                  f"-i include -I- -i loader -D{region} loader/loader.cpp -o loader/loader.o"

    compile_cmd = f"{MWCCEPPC} -c -Cpp_exceptions off -nodefaults -proc gekko -fp hard -lang=c++ -O4,s -inline on " \
                  f"-rtti off -sdata 0 -sdata2 0 -align powerpc -func_align 4 -str pool -enum int -DGEKKO " \
                  f"-i loader -i Petari/ -I- -i Petari/include -i {facelib_path} -i {rvl_sdk_path} -I- -i {trk_path} -I- -i {runtime_path} " \
                  f"-I- -i {msl_c_path} -I- -i {jsystem_path} -I- -i {nw4r_path} -i include -D{region} " \
                  f"loader/loader.cpp -o loader/loader.o" 

    kamek_cmd = f"{KAMEK} loader/loader.o -static=0x80001800 -externals={SYMBOLS}/{region}.txt " \
                f"-output-riiv={outputPath}/riivo_{region}.xml " \
                f"-output-kamek={outputPath}/Loader{getregionletter(region)}.bin " \
                f"-output-dolphin={outputPath}/Dolphin{getregionletter(region)}.ini"

    print(f"Building target {region}!")

    if os.path.exists(f"deps/{region}.dol"):
        kamek_cmd += f" -input-dol=deps/{region}.dol -output-dol=bin/{region}.dol"

    if subprocess.call(compile_cmd, shell=True) != 0:
        err("Compiling failed.")

    if subprocess.call(kamek_cmd, shell=True) != 0:
        err("Linking failed.")

    if buildFullXML:
        loaderPatches = open(f"{outputPath}/riivo_{region}.xml", "r").read()
        fullXMLBody = f"""<wiidisc version="1">
	<id game="RMG{getregionletter(region)}" />
	<options>
		<section name="Syati Loader">
			<option name="Super Mario Galaxy">
				<choice name="Enabled">
					<patch id="syati" />
				</choice>
			</option>
		</section>
	</options>
	<patch id="syati">
		{loaderPatches}
		<file disc="/CustomCode/CustomCode_USA.bin" external="CustomCode_USA.bin" create="true" />
	</patch>
</wiidisc>"""
        open(f"{outputPath}/riivo_{region}.xml", "w").write(fullXMLBody)

    print("Done!")


if __name__ == '__main__':
    isNextArgOutput = False
    buildFullXML = False
    outputPath = ""
    region = ""
    for currentArg in sys.argv:
        if (currentArg == "buildloader.py"):
            continue
        if (isNextArgOutput):
            outputPath = currentArg
            isNextArgOutput = False
        elif (currentArg == "-o"):
            isNextArgOutput = True
        elif (currentArg == "--full-xml"):
            buildFullXML = True
        else:
            region = currentArg
    if region not in REGIONS:
        print("Did not specify a (valid) target region, building all targets!")
        prepare_bin()
        for region in REGIONS:
            build(region, outputPath or "loader/", buildFullXML)
    else:
        prepare_bin()
        build(region, outputPath or "loader/", buildFullXML)
