# Toilet Visitor Counter

Simple Arduino based project that counts some room (like toilet) visitors by sensing when someone pass the entry. It was insiped by bicycle counted spotted during one of the trips.

### Key features

- Stays asleep most of the time, 2 month of expected battery life
- Keeps 2 numbers - daily and total visits. Total is stored in EEPROM, while daily is reset on power on
- Checks twice per second if someone present in range
- When detected - displays 2 numbers on the 8-digit display, reserving 4 digits for todays visits, and 4 more for total visits

### Components

- Arduino Pro mini board (Atmega328P)
- HC-SR04 ultra-sound sensor
- MAX7219 based 8-number 7-segment display

### Low power hardware modifications

Arduino Pro Mini board is not really designed for low power applications (at least Chinese clones aren't). When board is asleep it eats 10-15mA of power, most of it being a power LED that can be easily removed. This will get you down to 3mA, ehich doesn't sound like much, but with small batteries it will be accountable for the most of the consumption. Component that needs to go is linear stailizer (whish is not used when powered via VCC pin anyway). After that sleep power consuption goes below 10 uA, which is acceptable.

Next component is MAX7219 display, which luckily has POWER DOWN mode, enabled via software. When enabled it will use around 20 uA.

Last component is HC-SR04 ultra-sound sensor, it is not smart enough to enable low power mode, therefore I power it via Arduino Pro Mini pin, and only turn it on twice per second (you need to wait around 100 ms after turning on for it to release realistic numbers)

With above setup I'm hoping to have around 2 month of battery life with 2000mah li-ion battery (not sure about the actual capaity, it was salvaged from Dell laptop).

### Cardboard Prototype

## Demo 

![Demo](/doc/VID_20220511_204608.gif)