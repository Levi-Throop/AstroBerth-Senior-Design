import socket 

import time 

 

# create a socket and bind it to a port 

s = socket.socket() 

s.bind(('0.0.0.0', 8091)) 

s.listen(0) 

 

# keep looping until "End Program" is received as a message 

 

message2 = input("-->") 

 

message = "" 

while message != "End Program": 

 

    # wait foro a client to connect 

    print("Looking for Client:") 

    client, addr = s.accept() 

 

    # receive data from the client 

    content = client.recv(4096) 

    print(content) 

    client.send(message2.encode()) 

    # read the contents of the filoooonone 

    with open('C:/Users/delri/coords.txt', 'r') as f: 

        while True: 

            content = client.recv(4096).decode() 

            content = content.split("#", 3) 

            i = 0 

            for x in content: 

                print(x) 

                i += 1 

                if (i >= 3): 

                    break 

            print("\n") 

            #print(content) 

            # move the file pointer to the beginning of the file 

            f.seek(0, 0) 

 

            # read a line from the file 

            line = f.readline() 

 

            # if there are no more lines, wait and try again 

            if not line: 

                time.sleep(1) 

                continue 

 

            # skip empty liness 

            if not line.strip(): 

                continue 

 

            # parse the contents of the line to extract x, y, and z coordinates 

            try: 

                line = line.strip().replace('[1]', '') 

                x, y, z = map(float, line.split(',')) 

                print("Cargo Bag Coordinates: ", x, y, z) 

            except ValueError: 

                print("Error: could not parse line as x y z coordinates") 

                continue 

 

            # check if the coordinates meet a certain condition 

            if (-3.00 > x > -4.00) and (-1.00 > y > -2.00) and (7.60 < z < 8.00) : 

                message = "Cargo Bag Reached the approach point B" 

                print(message) 

                #client.send(message.encode()) 

                #message = "" 

 

            if (4.90 < z < 8.10) : 

                if x > -3.00 : 

                    print("Move the bag", -3.00+x, "Units to the up") 

                elif x < -4.00 : 

                    print("Move the bag", -4.00-x, "Units to the down") 

                if y > -1.00 : 

                    print("Move the bag", -1.00+y, "Units to the left") 

                elif y < -2.00 : 

                    print("Move the bag", -2.00-y, "Units to the right") 

 

            if (-1.80 > x > -2.20) and (-0.70 > y > -1.00) and (4.00 < z < 4.50) : 

                message = "Cargo Bag Reached the approach point A" 

                print(message) 

 

            if (0.8 < z < 4.8): 

                if x > -1.80 : 

                    print("Move the bag", -1.80+x, "Units to the up") 

                elif x < -2.20 : 

                    print("Move the bag", -2.20-x, "Units to the down") 

                if y > -0.70 : 

                    print("Move the bag", -0.70+y, "Units to the left") 

                elif y < -1.00 : 

                    print("Move the bag", -1.00-y, "Units to the right") 

 

            if (0.0 > x > -0.25) and (0.15 > y > -0.15) and (0 < z < 0.46) : 

                message = "Cargo Bag Is Connected with Berth Fixture!" 

                print(message) 

            # listen for messages from the client 

            try: 

                msg = client.recv(1024).decode().strip() 

                if msg: 

                    print("Message from client:", msg) 

            except socket.error as e: 

                print("Error receiving message from client:", e) 

 

    # close the connection with the client 

    print("Closing connection") 

    client.close() 

    print("Connection closed") 