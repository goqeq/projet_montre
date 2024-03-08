import datetime
import serial
import serial.tools.list_ports

# Récupérer la liste des ports série disponibles
ports = serial.tools.list_ports.comports()

# Afficher les ports disponibles
print("Ports disponibles :")
for port, desc, hwid in sorted(ports):
    print("{}: {}".format(port, desc))

# Demander à l'utilisateur de choisir un port
port_com = input("Entrez le port souhaité : ")

# Ouvrir la connexion série
ser = serial.Serial(port=port_com, baudrate=9600)


maintenant = datetime.datetime.now()

next_second = int(maintenant.second) + 1

print(maintenant, next_second)
while True:
    maintenant = datetime.datetime.now()

    if next_second == int(maintenant.second):
        ser.write(str(maintenant).encode('UTF-8'))
        print("TIME : ", next_second, maintenant)
        break

while True:
    # Obtenir la date et l'heure actuelles
    maintenant = str(datetime.datetime.now())

    try:
        # Lire et afficher la réponse du port série
        value = ser.readline().decode('utf-8')

    except:
        value = ser.readline().decode()

    print(value, maintenant)
