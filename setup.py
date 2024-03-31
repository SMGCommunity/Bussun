import urllib.request
import io
from zipfile import ZipFile

kamek = "https://mariogalaxy.org/Kamek-v1.zip"
cw = "http://shibbo.net/smg/Compilers.zip"

def setup():
    with urllib.request.urlopen(cw) as response:
        data = io.BytesIO(response.read())
        with ZipFile(data, "r") as zip:
            zip.extractall("Compilers")
    with urllib.request.urlopen(kamek) as response:
        data = io.BytesIO(response.read())
        with ZipFile(data, "r") as zip:
            zip.extractall("Kamek")


if __name__ == "__main__":
    setup()