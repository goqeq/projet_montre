from PIL import Image, ImageDraw
import math

# Taille de l'image
width = 240
height = 240

# Créer une nouvelle image avec un fond transparent
img = Image.new('RGB', (width, height), (0, 0, 0))

# Créer un objet "draw" pour dessiner sur l'image
draw = ImageDraw.Draw(img)

# Position du centre du cercle
center_x = 120
center_y = 120

# Diamètre du cercle
diameter = 240

# Longueur des barres
big_bar_length = 20
small_bar_length = 6  # Longueur des petites barres

# Dessiner les 12 barres autour du centre du cercle
for i in range(12):
    angle = math.radians(i * 30)  # Convertir l'angle en radians
    x1_big = center_x + int(math.cos(angle) * diameter / 2)  # Coordonnée x du début de la grande barre
    y1_big = center_y + int(math.sin(angle) * diameter / 2)  # Coordonnée y du début de la grande barre
    x2_big = center_x + int(math.cos(angle) * (diameter / 2 - big_bar_length))  # Coordonnée x de la fin de la grande barre
    y2_big = center_y + int(math.sin(angle) * (diameter / 2 - big_bar_length))  # Coordonnée y de la fin de la grande barre
    draw.line([(x1_big, y1_big), (x2_big, y2_big)], fill='white', width=2)

    # Dessiner les petites barres entre les grandes barres
    for j in range(4):
        small_angle = math.radians(i * 30 + j * 7.5)  # Angle pour les petites barres
        x1_small = center_x + int(math.cos(small_angle) * (diameter / 2))  # Coordonnée x du début de la petite barre
        y1_small = center_y + int(math.sin(small_angle) * (diameter / 2))  # Coordonnée y du début de la petite barre
        x2_small = center_x + int(math.cos(small_angle) * (diameter / 2 - small_bar_length))  # Coordonnée x de la fin de la petite barre
        y2_small = center_y + int(math.sin(small_angle) * (diameter / 2 - small_bar_length))  # Coordonnée y de la fin de la petite barre
        draw.line([(x1_small, y1_small), (x2_small, y2_small)], fill='white', width=1)

# Enregistrer l'image sous forme de fichier PNG
img.save('barres_autour_cercle.png')

# Afficher l'image
img.show()