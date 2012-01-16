//------------------------------------------------------------------------------------------------------------------------
// Nanode Web IR Remote Control
// By Nathan Chantrell http://nathan.chantrell.net
//
// Web server based on EtherCard version of RESTduino by Andrew D Lindsay http://blog.thiseldo.co.uk
//------------------------------------------------------------------------------------------------------------------------

//#define DEBUG // uncomment for serial monitor debug output

#include <IRremote.h> // http://www.arcfn.com/2009/08/multi-protocol-infrared-remote-library.html

IRsend irsend; // Initialise the IRsend library. IR LED must be on Digital Pin 3

//########################################################################################################################
// If using Raw IR Commands we need to store these in flash or the ATmega will run out of RAM
//########################################################################################################################
#include <avr/pgmspace.h> // Required to store the raw data in flash (program) memory

// The Raw IR Commands gathered from the IRrecvDump sketch in the IRremote examples. 
// Remove the first digit group, make all positive and add commas between each group.
unsigned int DabPower[68] PROGMEM = {4500, 4500, 600, 550, 550, 1650, 600, 550, 600, 550, 550, 550, 550, 600, 550, 550, 550, 1650, 600, 550, 550, 1700, 550, 550, 600, 550, 550, 550, 600, 550, 550, 550, 600, 1600, 600, 1650, 600, 600, 500, 600, 550, 550, 550, 600, 550, 550, 550, 550, 600, 550, 550, 550, 600, 1650, 600, 1600, 600, 1650, 600, 1650, 600, 1650, 600, 1650, 600, 1650, 600};
unsigned int DabPreset1[68] PROGMEM = {4500, 4500, 600, 550, 550, 1650, 600, 550, 550, 550, 600, 500, 600, 550, 600, 500, 600, 1650, 600, 550, 600, 1650, 550, 550, 600, 550, 550, 550, 600, 500, 600, 550, 650, 1550, 600, 1650, 600, 1650, 600, 550, 550, 550, 600, 1650, 600, 550, 550, 550, 650, 450, 600, 550, 650, 450, 600, 1650, 600, 1650, 600, 500, 600, 1650, 600, 1650, 600, 1650, 600};
unsigned int DabPreset2[68] PROGMEM = {4500, 4500, 600, 500, 600, 1650, 600, 500, 600, 550, 600, 500, 650, 500, 550, 550, 600, 1650, 600, 550, 550, 1700, 550, 550, 600, 500, 600, 550, 550, 550, 600, 500, 600, 1650, 600, 1650, 600, 1650, 600, 550, 600, 1650, 550, 550, 600, 550, 550, 550, 600, 500, 600, 500, 600, 550, 600, 1650, 550, 550, 600, 1650, 600, 1650, 600, 1650, 600, 1650, 600};
unsigned int DabPreset3[68] PROGMEM = {4550, 4450, 600, 550, 600, 1650, 550, 550, 600, 550, 550, 550, 600, 550, 550, 550, 600, 1650, 600, 500, 600, 1650, 600, 500, 600, 550, 600, 500, 600, 550, 550, 550, 600, 1650, 600, 1650, 600, 1650, 600, 500, 600, 550, 550, 550, 600, 500, 600, 550, 600, 500, 600, 550, 550, 550, 600, 1650, 600, 1650, 600, 1650, 600, 1650, 550, 1650, 600, 1650, 650};
unsigned int DabPreset4[68] PROGMEM = {4500, 4500, 600, 550, 550, 1700, 550, 550, 600, 550, 550, 550, 600, 550, 550, 550, 550, 1650, 600, 550, 550, 1700, 550, 600, 550, 550, 550, 550, 600, 550, 550, 550, 600, 1650, 600, 550, 550, 550, 600, 1600, 650, 550, 550, 1650, 550, 600, 550, 550, 550, 600, 550, 1650, 600, 1650, 600, 550, 550, 1650, 600, 550, 550, 1650, 600, 1650, 600, 1650, 600};
unsigned int DabPreset5[68] PROGMEM = {4500, 4500, 600, 550, 550, 1700, 550, 550, 600, 550, 550, 550, 600, 500, 600, 550, 600, 1650, 550, 550, 600, 1650, 550, 550, 600, 550, 550, 550, 600, 550, 550, 550, 600, 1650, 600, 500, 600, 550, 550, 1700, 550, 1650, 600, 550, 550, 550, 600, 550, 550, 550, 600, 1650, 600, 1650, 600, 500, 600, 550, 600, 1650, 550, 1650, 600, 1650, 600, 1650, 600};
unsigned int DabPreset6[68] PROGMEM = {4500, 4500, 600, 550, 550, 1700, 550, 550, 600, 500, 600, 550, 550, 550, 600, 550, 550, 1650, 600, 550, 600, 1650, 550, 550, 600, 550, 550, 550, 600, 550, 550, 550, 600, 1650, 600, 500, 600, 500, 600, 1650, 600, 600, 500, 550, 600, 550, 550, 550, 600, 550, 550, 1700, 550, 1700, 550, 550, 600, 1600, 600, 1650, 600, 1650, 600, 1650, 600, 1650, 600};
unsigned int DabPreset7[68] PROGMEM = {4550, 4450, 600, 550, 600, 1650, 550, 550, 600, 550, 550, 550, 600, 550, 550, 550, 600, 1650, 600, 500, 600, 1650, 600, 500, 600, 550, 600, 500, 600, 550, 550, 550, 600, 1650, 600, 1650, 600, 550, 550, 1650, 600, 550, 550, 1650, 600, 550, 600, 500, 600, 550, 600, 500, 600, 1650, 600, 550, 550, 1700, 550, 550, 600, 1650, 600, 1600, 600, 1650, 600};
unsigned int DabPreset8[68] PROGMEM = {4550, 4450, 600, 550, 550, 1650, 600, 550, 600, 500, 600, 500, 600, 550, 600, 500, 600, 1650, 600, 550, 550, 1700, 550, 550, 600, 550, 550, 550, 600, 500, 600, 550, 600, 1650, 550, 1650, 600, 550, 550, 1700, 550, 1700, 550, 550, 600, 550, 550, 550, 600, 500, 600, 550, 600, 1650, 550, 550, 600, 500, 600, 1650, 600, 1650, 600, 1650, 600, 1650, 600};
unsigned int DabPreset9[68] PROGMEM = {4500, 4500, 600, 550, 550, 1700, 550, 550, 600, 550, 550, 550, 600, 500, 600, 550, 600, 1600, 600, 550, 550, 1700, 550, 550, 600, 550, 550, 550, 600, 550, 550, 550, 600, 1650, 600, 1650, 600, 500, 600, 1650, 550, 550, 600, 550, 550, 550, 600, 550, 550, 550, 600, 550, 550, 1700, 550, 550, 600, 1650, 600, 1650, 550, 1650, 600, 1650, 600, 1650, 600};
unsigned int DabPreset10[68] PROGMEM = {4500, 4500, 600, 550, 550, 1700, 550, 550, 600, 550, 550, 550, 600, 550, 550, 550, 600, 1650, 600, 500, 600, 1650, 600, 500, 600, 550, 550, 550, 600, 550, 550, 550, 600, 1650, 600, 550, 550, 1650, 600, 1650, 600, 1650, 600, 500, 600, 550, 550, 550, 600, 550, 550, 1700, 550, 550, 600, 550, 550, 550, 600, 1650, 600, 1600, 600, 1650, 600, 1650, 600};
//########################################################################################################################

#include "EtherCard.h" // https://github.com/jcw/ethercard
#include <NanodeMAC.h> // https://github.com/thiseldo/NanodeMAC

static uint8_t mymac[6] = { 0,0,0,0,0,0 }; // mac will be filled in by NanodeMAC
static uint8_t myip[4] = { 192,168,0,188}; // ip address
static uint8_t gwip[4] = { 192,168,0,100 }; // gateway

#define MYWWWPORT 80    // listen port for tcp/www (max range 1-254)

#define BUFFER_SIZE 700
byte Ethernet::buffer[BUFFER_SIZE];
BufferFiller bfill;

NanodeMAC mac( mymac ); // get Nanode's mac address

#define STR_BUFFER_SIZE 22
static char strbuf[STR_BUFFER_SIZE+1];

// prepare the webpage by writing the data to the tcp send buffer
uint16_t print_webpage()
{
  bfill = ether.tcpOffset();
  bfill.emit_p(PSTR(
    "HTTP/1.0 200 OK\r\n"
    "Content-Type: text/html\r\n"
    "Pragma: no-cache\r\n"
    "\r\n"
    "<html><body><h1>Nanode Web IR Remote control</h1>"
    "<a href=\"/0\">Power on/off</a><br><br>"
    "<b>Station presets</b><br>"
    "<a href=\"/1\">(1) BBC Radio 1</a><br>"
    "<a href=\"/2\">(2) BBC Radio 2</a><br>"
    "<a href=\"/3\">(3) BBC Radio 3</a><br>"
    "<a href=\"/4\">(4) BBC Radio 4</a><br>"
    "<a href=\"/5\">(5) BBC Radio 5 Live</a><br>"
    "<a href=\"/6\">(6) BBC 6 Music</a><br>"
    "<a href=\"/7\">(7) BBC Radio 4 Extra</a><br>"
    "<a href=\"/8\">(8) TalkSport</a><br>"
    "<a href=\"/9\">(9) Key 103</a><br>"
    "<a href=\"/10\">(10) Absolute Radio</a><br>"
    "</body></html>"));
  return bfill.position();
}

#define CMDBUF 50

int16_t process_request(char *str)
{
  int8_t r=-1;
  int8_t i = 0;
  char clientline[CMDBUF];
  int index = 0;
  int plen = 0;
  
#ifdef DEBUG
  Serial.println( str );
#endif

  char ch = str[index];
  
  while( ch != ' ' && index < CMDBUF) {
    clientline[index] = ch;
    index++;
    ch = str[index];
  }
  clientline[index] = '\0';

#ifdef DEBUG
  Serial.println( clientline );
#endif

  // convert clientline into a proper
  // string for further processing
  String urlString = String(clientline);

  // extract the operation
  String op = urlString.substring(0,urlString.indexOf(' '));

  // we're only interested in the first part...
  urlString = urlString.substring(urlString.indexOf('/'), urlString.indexOf(' ', urlString.indexOf('/')));

  // put what's left of the URL back in client line
  urlString.toCharArray(clientline, CMDBUF);

  // get the first parameter
  char *button = strtok(clientline,"/");

  if(button != NULL){

  // send the IR Command
#ifdef DEBUG
      Serial.println("sending IR command");
#endif
            
  int selectedButton = button[0] -'0';

//########################################################################################################################
// If using Raw IR Commands
//########################################################################################################################

  // get the relevant code from PROGMEM
  unsigned int rawCode[68];

   switch(selectedButton)
   {
   case 0: for(int i=0; i<68; i++){rawCode[i]=(pgm_read_word(&DabPower[i]));} break; // Power
   case 1: for(int i=0; i<68; i++){rawCode[i]=(pgm_read_word(&DabPreset1[i]));} break; // Preset 1       
   case 2: for(int i=0; i<68; i++){rawCode[i]=(pgm_read_word(&DabPreset2[i]));} break; // Preset 2
   case 3: for(int i=0; i<68; i++){rawCode[i]=(pgm_read_word(&DabPreset3[i]));} break; // Preset 3
   case 4: for(int i=0; i<68; i++){rawCode[i]=(pgm_read_word(&DabPreset4[i]));} break; // Preset 4
   case 5: for(int i=0; i<68; i++){rawCode[i]=(pgm_read_word(&DabPreset5[i]));} break; // Preset 5
   case 6: for(int i=0; i<68; i++){rawCode[i]=(pgm_read_word(&DabPreset6[i]));} break; // Preset 6
   case 7: for(int i=0; i<68; i++){rawCode[i]=(pgm_read_word(&DabPreset7[i]));} break; // Preset 7
   case 8: for(int i=0; i<68; i++){rawCode[i]=(pgm_read_word(&DabPreset8[i]));} break; // Preset 8
   case 9: for(int i=0; i<68; i++){rawCode[i]=(pgm_read_word(&DabPreset9[i]));} break; // Preset 9
   case 10: for(int i=0; i<68; i++){rawCode[i]=(pgm_read_word(&DabPreset10[i]));} break; // Preset 10
   } 
   irsend.sendRaw(rawCode,68,38); // send the IR code

//########################################################################################################################
// For codes that the IR library has protocols for you can do the following instead:
//   case 0: irsend.sendSony(0xa90, 12); break; // Sony TV power code
//########################################################################################################################

  // show menu again
  return print_webpage();
        
  } else {         
  // no command sent - show menu
  return print_webpage();
  }
 
  return plen;
}

void setup(){

#ifdef DEBUG
  Serial.begin(19200);
  Serial.println("Nanode Web IR Remote Control");
#endif

  if (ether.begin(sizeof Ethernet::buffer, mymac) == 0) {
#ifdef DEBUG
    Serial.println( "Failed to access Ethernet controller");
#endif
    while(1);
  }
  
  // Setup static IP address
  ether.staticSetup(myip, gwip);

#ifdef DEBUG
  Serial.println("Ready");
#endif

}

void loop(){
  uint16_t plen, dat_p;
  int8_t cmd;

  while(1) {
    // read packet, handle ping and wait for a tcp packet:
   dat_p=ether.packetLoop(ether.packetReceive());

    /* dat_p will be unequal to zero if there is a valid http get */
    if(dat_p==0){
      // no http request
      continue;
    }

    // tcp port 80 begin
    if (strncmp("GET ",(char *)&(Ethernet::buffer[dat_p]),4)!=0){
      // head, post and other methods:
      dat_p = print_webpage();
      goto SENDTCP;
    }

    // just one web page in the "root directory" of the web server
    if (strncmp("/ ",(char *)&(Ethernet::buffer[dat_p+4]),2)==0){
#ifdef DEBUG
      Serial.println("GET / request");
#endif
      dat_p = print_webpage();
      goto SENDTCP;
    }
    dat_p = process_request((char *)&(Ethernet::buffer[dat_p+4]));
    
SENDTCP:
      if( dat_p )
        ether.httpServerReply( dat_p);

    // tcp port 80 end
  }

}

