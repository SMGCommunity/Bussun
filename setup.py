import urllib.request
import io
from zipfile import ZipFile

kamek = "https://cdn.discordapp.com/attachments/1119750120657911849/1145047376936050730/Kamek.zip"
cw = "http://shibbo.net/smg/Compilers.zip"

def setup():
    with urllib.request.urlopen(cw) as response:
        data = io.BytesIO(response.read())
        with ZipFile(data, "r") as zip:
            zip.extractall("Compilers")
    headers = {}
    headers["User-Agent"]='Mozilla/5.0 (X11; Ubuntu; Linux i686; rv:48.0) Gecko/20100101 Firefox/48.0'
    request = urllib.request.Request(kamek, headers=headers)
    with urllib.request.urlopen(request) as response:
        data = io.BytesIO(response.read())
        with ZipFile(data, "r") as zip:
            zip.extractall("Kamek")


if __name__ == "__main__":
    setup()