# netatmo-underfloor-heating


An attempt to connect my underfloor heating to the netatmo thermometer API. I allready had smart radiator valves, however I could not control my underfloor heating. Therefore if a radiator demanded heat als my underfloor heating was heating up. I decided that it should be possible

I used a standard ESP8266 with this ESP01/01S relay https://www.hobbyelectronica.nl/product/esp-01-relais-module/

On the esp8266 I run the ESP8266.ino script. Don't forget to add the right libraries and boards. Got the inspiration from several other contributions. Most notably disordenado77 https://github.com/desordenado77/esp8266_netatmo_acController However I did not get the https autorization and request running on the ESP8266. On this website I found a workaround using a PHP script on a free webserver: https://www.instructables.com/Netatmo-DualScreen-Station/ To read about how to program your ESP8266 with arduino see for example https://randomnerdtutorials.com/

You can run the PHP script on a free webhost. For example https://www.000webhost.com/ Simply put the index.php file in the public_html folder.

The relay I connected to two thermoelectric actuators from Honeywell https://www.amazon.nl/Honeywell-Mt4-230-NC-Thermische-Aandrijving-Gesloten/dp/B00MPJPZ7M/ref=asc_df_B00MPJPZ7M/?tag=nlshogostdde-21&linkCode=df0&hvadid=430530449181&hvpos=&hvnetw=g&hvrand=5230586295065102674&hvpone=&hvptwo=&hvqmt=&hvdev=c&hvdvcmdl=&hvlocint=&hvlocphy=9065078&hvtargid=pla-420297076990&psc=1. I used the NC (normally closed) type. For underfloor heating this seems the logical option. If you decide to use NO (Normally open) type the only change you have to make is in how to do the wiring with the relay. Take note that the running time of these type of actuators is typically 3 to 5 minutes. At first I thought my relay was malfunctioning, but I just had to be a bit more patient :)

Everything is running for over a week now without problems. I probably will add some security layers in the future, but for now I'm very happy I made it work.
