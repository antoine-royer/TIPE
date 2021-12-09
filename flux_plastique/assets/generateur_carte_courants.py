from PIL import Image


"""
Correspondance couleur / courant :

#000000 (= 0)   : (60, 50) [droite]
#1f1f1f (= 31)  : (60, 40) [droite, bas]
#393939 (= 57)  : (50, 40) [bas]
#555555 (= 85)  : (40, 40) [gauche, bas]
#727272 (= 114) : (40, 50) [gauche]
#919191 (= 145) : (40, 60) [gauche, haut]
#b0b0b0 (= 176) : (50, 60) [haut]
#d1d1d1 (= 209) : (60, 60) [droite, haut] 
"""

# Constante des courants
MID = "50"
LOW = "49"
HIG = "51"


worldmap = Image.open("courants.png")

size = worldmap.size
output = "#include \"../include/carte_vecteurs.h\"\n\n" + f"uint8_t courants[{size[1]}][{size[0]}][2] = " + "{\n{"


streams = {
    0:   f"{HIG}, {MID}", # droite 
    31:  f"{LOW}, {LOW}", # droite, bas
    57:  f"{MID}, {LOW}", # bas
    85:  f"{LOW}, {LOW}", # gauche, bas
    114: f"{LOW}, {MID}", # gauche
    145: f"{LOW}, {HIG}", # gauche, haut
    176: f"{MID}, {HIG}", # haut
    209: f"{HIG}, {HIG}", # droite, haut
    255: f"{MID}, {MID}", # pas de courant
}


def get_stream(pixel):
    for pxl_id in streams:
        if pixel <= pxl_id:
            return streams[pxl_id]
    return f"{MID}, {MID}"


for y in range(size[1]):
    for x in range(size[0]):

        pixel = worldmap.getpixel((x, y))
        
        if pixel == (0, 255, 0):
            output += "{0, 0}, "

        else: # pixel[0] in courants:
            stream = get_stream(pixel[0])
            output += "{" + stream + "}, "

    output = output[:-2] + "},\n{"

output = output[:-1] + "};"


with open("../src/carte_vecteurs.c", "w") as file:
    file.write(output)
