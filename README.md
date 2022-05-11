# Toilet Visitor Counter

Simple Arduino based project that counts some room (like toilet) visitors by sensing when someone pass the entry. It was insiped by bicycle counted spotted during one of the trips.

![image](https://user-images.githubusercontent.com/5459747/167929234-2f4a12d2-9af6-4ceb-9182-f7b6de29c8dc.png)

### Key features

- Stays asleep most of the time, 2 month of expected battery life
- Keeps 2 numbers - daily and total visits. Total is stored in EEPROM, while daily is reset on power on (and once per day)
- Checks twice per second if someone present in range
- When detected - displays 2 numbers on the 8-digit display, reserving 4 digits for todays visits, and 4 more for total visits

### Components

- ![image](https://user-images.githubusercontent.com/5459747/167928200-6215dd4a-0cbf-4569-b48d-bc7d8308c6da.png) Arduino Pro mini board (Atmega328P) 
- ![image](https://user-images.githubusercontent.com/5459747/167928250-f4e1112f-d024-45d7-84eb-6673ddffa605.png) HC-SR04 ultra-sound sensor
- ![image](https://user-images.githubusercontent.com/5459747/167928309-eb3da741-6fcd-4f84-bb07-26349ec2c27c.png) MAX7219 based 8-digit 7-segment display

### Low power hardware modifications


Arduino Pro Mini board is not really designed for low power applications (at least Chinese clones aren't). When board is asleep it eats 10-15mA of power, most of it being a power LED that can be easily removed. This will get you down to 3mA, ehich doesn't sound like much, but with small batteries it will be accountable for the most of the consumption. Component that needs to go is linear stailizer (whish is not used when powered via VCC pin anyway). After that sleep power consuption goes below 10 uA, which is acceptable.

Next component is MAX7219 display, which luckily has POWER DOWN mode, enabled via software. When enabled it will use around 20 uA.

Last component is HC-SR04 ultra-sound sensor, it is not smart enough to enable low power mode, therefore I power it via Arduino Pro Mini pin, and only turn it on twice per second (you need to wait around 100 ms after turning on for it to release realistic numbers)

With above setup I'm hoping to have around 2 month of battery life with 2000mah li-ion battery (not sure about the actual capaity, it was salvaged from Dell laptop).

### Cardboard Prototype

First prototype with jumper wires

![image](https://user-images.githubusercontent.com/5459747/167928473-7f3bee7d-3914-40bc-8f70-cd98d41d072c.png)

Next packed into thick cardboard that you'll find in IKEA furniture packaging (for home projects I prefer this solution over 3D-printing due to simplicity and lack of plastick)

![image](https://user-images.githubusercontent.com/5459747/167928724-b6257da1-4b7a-484d-8615-4b7c4a386ad3.png)

All wires connected. Much more reliable than jump leads.

![image](https://user-images.githubusercontent.com/5459747/167928976-a709dff3-7fa8-47d1-abc6-5cbcdd5060d9.png)

And finally

![image](https://user-images.githubusercontent.com/5459747/167929594-92a8d80a-503c-4c5a-989d-c813be67cd86.png)

Hot glue usgae during installation is mandatory I'd assume.

## Demo 

![Demo](/doc/VID_20220511_204608.gif)
