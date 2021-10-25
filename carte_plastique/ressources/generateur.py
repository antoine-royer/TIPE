from PIL import Image


worldmap = Image.open("carte_vierge.png")

size = worldmap.size
output = "#include \"../include/carte_vecteurs.h\"\n\n" + f"uint8_t courants[{size[1]}][{size[0]}][2] = " + "{\n{"

courants = {
    0:   "{70, 50}, ", # droite 
    31:  "{70, 30}, ", # droite, bas
    57:  "{50, 30}, ", # bas
    85:  "{30, 30}, ", # gauche, bas
    114: "{30, 50}, ", # gauche
    145: "{30, 70}, ", # gauche, haut
    176: "{50, 70}, ", # haut
    209: "{70, 70}, ", # droite, haut
    255: "{50, 50}, ", # pas de courant
}

case_count = 0
for y in range(size[1]):
    for x in range(size[0]):

        pixel = worldmap.getpixel((x, y))
        
        if pixel == (0, 255, 0):
            output += "{0, 0}, "

        elif pixel[0] in courants:
            case_count += 1
            output += courants[pixel[0]]

        else:
            output += "{50, 50}, "

    output = output[:-2] + "},\n{"

output = output[:-1] + "};"


with open("../src/carte_vecteurs.c", "w") as file:
    file.write(output)

print(case_count)

