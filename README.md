# AstroBerth-Senior-Design
# Project Summary

Our team was tasked with solving the problem of inefficient cargo storage on the International Space Station (ISS). The current storage system uses bungee cords to hold cargo bags in place, resulting in disorganization and wasted time for astronauts when stowing and retrieving cargo.

To address this issue, we formulated a solution that utilizes the capabilities of the Astrobee robot, which is already deployed on the ISS. Specifically, we created a cargo berth fixture that is mounted on the walls of the ISS and uses an esp32cam microprocessor, a camera, and a magnet to allow the Astrobee to autonomously stow and retrieve cargo bags.

Our cargo berth fixture incorporates a fiducial marker and a steel strike plate on the bags, which allows the fixture to track the marker and send coordinates to the Astrobee to guide it in mating the magnet and steel strike plate on the bag, thus successfully stowing the bag. The fixture also includes a switch that signals when the bag has been mounted properly, as well as a deep sleep mode and a light module switch. 

The deep sleep mode ensures that the fixture is not wasting energy when not in use, while the light module switch enables the Astrobee's built-in flashlight to activate the fixture and prepare it for the next task. When designing our solution, we had ease of use and safety in mind. The berth fixture is constructed using lightweight material and fasteners that stay in place after they are unscrewed. This ensures that when the crew changes out the batteries which power the device, there is zero chance for the hardware to fall out and get lost, possibly causing issues with other systems.

We also designed the fixture to be fastened to the wall of the ISS using Velcro. Using this material allows the fixture to be secured but easily removed if they decide to relocate them or need to make any adjustments. Also, the steel strike plate has been attached to the front of the cargo bag allowing any interaction with the magnet on the fixture to not interfere with any precious materials or electronics the bag may contain. Of course, when packing the materials, the ground crew should package the bag in such a way that most vulnerable items to be placed farthest away from the plate as a counter measure.

Lastly, the berth fixture was designed to be as power conservative as possible. Our thought process on this, is that if we want to utilize the Astrobee to take over the task of stowing/retrieving the cargo bags in an autonomous way, requiring the crew to manually change out the power source too frequently would be counterproductive. That is why we included the flashlight module with the goose neck attachment and the mount switch on the face of the fixture. Together, they allow the berth fixture to go into deep sleep mode and only power on when Astrobee needs to remove a cargo bag from its stowed location since the magnet is always magnetized until the berth fixture is powered on and sends current to it.

# Project Block Diagram
![Alt text](/3_21_23%20Demo%20Block.png "Optional title")
## Block Diagram

The block diagram outlines the interactions between the different systems involved in our project. The cargo berth fixture, located on the left side of the diagram, houses the magnet, camera, and power supply. It interacts with the cargo bag through fiducial tracking and mating with the steel strike plate. TCP communication over a local hotspot connection allows the fixture to receive commands from our Python host. The fiducial tracking program saves position coordinates which the host uses to guide the user in adjusting the position of the cargo bag during the mating process. This allows a team member to physically manipulate the bag and guide it to the berth fixture.

To simulate this process, we used a NASA-built simulation environment utilizing ROS and Gazebo. Our cargo berth fixture’s .urdf files and transform were added to the environment, allowing us to highlight the interaction between the fixture, robot, and bag in a virtual space.

# 3D Model Diagram
![Alt text](/model_diagram.png "Optional title")

### 3.3.3 3D Modeling Diagram 

The accompanying image displays a comprehensive breakdown of our model. The entire model was manufactured using 3D printing with PLA plastic and securely assembled with M4 inserts and machined screws. 

To ensure optimal performance, we carefully placed the cameras at a considerable distance from the magnet to allow uninterrupted reading of the fiducial marker when the bag is fully installed, as depicted in balloons 9 and 19. 

Balloon 1 illustrates the front plate of our cargo berth, which features precision cutouts specifically designed to accommodate the switch and magnet arrangement. These cutouts are prominently visible in balloons 5 and 13. Balloon 2 displays handles on either side of the AstroBerth, facilitating easy handling of the product. 

Balloon 3 portrays the backplate of the AstroBerth, ingeniously housing our batteries. Our design further incorporates a goose neck design, illustrated in balloon 10, that enables facile maneuvering of the light sensor on top of the cargo berth around the cargo bags. 

Finally, balloon 12 highlights the light sensor housing that encompasses our light sensor, specifically intended for deep sleep operation modes, reflecting our relentless pursuit of innovative solutions.
