
#include <esp_now.h>
#include <WiFi.h>

    #include <Adafruit_NeoPixel.h>
    #include <FastLED.h>
    #include <math.h>              // https://github.com/FastLED/FastLED
#define NUMLEDS 57        // Number of LEDs
#define NUMLEDS_2 44
#define NUMLEDS_3 43
#define NUMLEDS_4 60
#define NUMLEDS_5 60
#define DATA_PIN 19              // Connect your addressable LED strip to this pin.
#define DATA_PIN_2 21
#define DATA_PIN_3 18
#define DATA_PIN_4 5
#define DATA_PIN_5 17
#define SENSITIVITY 1023        // Ranges from 0 to 1023
#define MAX_BRIGHTNESS 250       // Ranges from 0 to 255
#define ENVELOPE_PIN A0           // Connect sound detector to this pin
#define SATURATION 200          // Ranges from 0 to 255
#define MINVAL 60
#define HUE_INIT 10
#define HUE_CHANGE 10
#define TIME_FACTOR_HUE 60
#define TIME_FACTOR_SAT 100
#define TIME_FACTOR_VAL 100
#define TEMPERATURE_1 Tungsten100W
#define TEMPERATURE_2 OvercastSky
#define DISPLAYTIME 20
#define BLACKTIME   3

//SoftwareSerial HC05 (0,1); // D7, D8, TX, RX , không thể kết nối trực tiếp TX và RX của HC05 vào chân TX và RX của arduino vì sẽ nap code không được, vì vâỵ cần tạo chân serial ảo để thay thế chân RX và TX bằng thư viện SofwareSerial.h
// nối chéo TX của hc05 n ối với Rx của arduino và ngược lại
CRGB leds[NUMLEDS];
CRGB leds_2[NUMLEDS_2];
CRGB leds_3[NUMLEDS_3];
CRGB leds_4[NUMLEDS_4];
CRGB leds_5[NUMLEDS_5];


byte brightness[255];
byte hue[NUMLEDS];
int analogVal;
int DELAY;
volatile int count = 0; // Biến volatile để xử lý trong ngắt
bool ledActive = false; // Biến để lưu trạng thái bật/tắt LED
#define LED_PIN     19
#define NUM_LEDS    60
#define BRIGHTNESS  255
#define LED_TYPE    WS2811
#define COLOR_ORDER GRB
char dieu_khien;
#define UPDATES_PER_SECOND 100
#define FRAMES_PER_SECOND 60

bool gReverseDirection = false;
CRGBPalette16 gPal;
int sound=A0;

#define NUM_LEDS 19

#define DATA_PIN 19
#define CLOCK_PIN 13
CRGBArray<NUM_LEDS> twoleds;

CRGBPalette16 currentPalette;
TBlendType    currentBlending;

extern CRGBPalette16 myRedWhiteBluePalette;
extern const TProgmemPalette16 myRedWhiteBluePalette_p PROGMEM;




typedef struct struct_message {
   int buttonState ;  // Trạng thái đèn (ON/OFF)
   int buttonState_2 ;
   int buttonState_3 ;
   int buttonState_4 ;
} struct_message;

struct_message controlData;

void OnDataRecv(const esp_now_recv_info *info, const uint8_t *data, int len) {
  memcpy(&controlData, data, sizeof(controlData));
  if(controlData.buttonState == LOW && controlData.buttonState_2 == LOW && controlData.buttonState_3 == LOW && controlData.buttonState_4 == LOW ){
    ChangePalettePeriodically();  
    static uint8_t astartIndex = 0;
    astartIndex = astartIndex + 1; 
    FillLEDsFromPaletteColors( astartIndex);
    confetti();
    FillLEDsFromPaletteColors2( astartIndex);
    confetti2();
    FillLEDsFromPaletteColors3( astartIndex);
    confetti3();
    FillLEDsFromPaletteColors4( astartIndex);
    confetti4();
    FillLEDsFromPaletteColors5( astartIndex);
    confetti5();
    Serial.println("1234-nhanh");
  }
  else if(controlData.buttonState == LOW && controlData.buttonState_2 == LOW && controlData.buttonState_3 == LOW){
    sinelon();
    sinelon2();
    juggle3();
    juggle4();
    juggle5();
    Serial.println("123-nhanh");
  }
  else if(controlData.buttonState == LOW && controlData.buttonState_2 == LOW && controlData.buttonState_4 == LOW){
    Espl2SDemo();
    Espl2SDemo2();
    Espl2SDemo3();
    Fire2012WithPalette4();
    Fire2012WithPalette5();
    Serial.println("124-nhanh");
  }
  else if(controlData.buttonState == LOW && controlData.buttonState_3 == LOW && controlData.buttonState_4 == LOW){
    ColorTemperatureEx();
    ColorTemperatureEx2();
    ColorTemperatureEx3();
    Espl2SDemo4();
    Espl2SDemo5();
    Serial.println("134-nhe");
  }
  else if(controlData.buttonState_2 == LOW && controlData.buttonState_3 == LOW && controlData.buttonState_4 == LOW){
    ChangePalettePeriodically();  
    static uint8_t astartIndex = 0;
    astartIndex = astartIndex + 1; 
    FillLEDsFromPaletteColors( astartIndex);
    FillLEDsFromPaletteColors2( astartIndex);
    FillLEDsFromPaletteColors3( astartIndex);
    ColorTemperatureEx4();
    ColorTemperatureEx5();
    Serial.println("234-nhe");
  }
  else if(controlData.buttonState == LOW && controlData.buttonState_2 == LOW){
      bpm();
      bpm2();
      bpm3();
      bpm4();
      bpm5();
    Serial.println("12-nhe");
  }
   
  else if(controlData.buttonState == LOW && controlData.buttonState_3 == LOW){
    confetti();
    confetti2();
    confetti3();
    confetti4();
    confetti5();
    Serial.println("13-loan_xa");
  }else if(controlData.buttonState == LOW && controlData.buttonState_4 == LOW){
    // ChangePalettePeriodically();  
    // static uint8_t astartIndex = 0;
    // astartIndex = astartIndex + 3; 
    // FillLEDsFromPaletteColors( astartIndex);
    sinelon();
    sinelon2();
    sinelon3();
    sinelon4();
    sinelon5();
    Serial.println("14-duoi");
  }else if(controlData.buttonState_2 == LOW && controlData.buttonState_3 == LOW ){
    pride();
    pride2();
    pride3();
    pride4();
    pride5();
    Serial.println("23-nhe");
  }else if(controlData.buttonState_2 == LOW && controlData.buttonState_4 == LOW ){
    juggle();
    juggle2();
    juggle3();
    juggle4();
    juggle5();
    Serial.println("24-nhanh");
  }else if(controlData.buttonState_3 == LOW && controlData.buttonState_4 == LOW ){
    Fire2012WithPalette();
    Fire2012WithPalette2();
    Fire2012WithPalette3();
    Fire2012WithPalette4();
    Fire2012WithPalette5();
    Serial.println("34-nhanh");
  }
  else if(controlData.buttonState == LOW){
    Espl2SDemo();
    Espl2SDemo2();
    Espl2SDemo3();
    Espl2SDemo4();
    Espl2SDemo5();
    Serial.println("1-nhe");
    FastLED.show();
  }
  else if(controlData.buttonState_2 == LOW){
    ColorTemperatureEx();
    ColorTemperatureEx2();
    ColorTemperatureEx3();
    ColorTemperatureEx4();
    ColorTemperatureEx5();
    Serial.println("2-nhe");
  }
  else if(controlData.buttonState_3 == LOW){
    ChangePalettePeriodically();  
    static uint8_t astartIndex = 0;
    astartIndex = astartIndex + 1; 
    FillLEDsFromPaletteColors( astartIndex);
    FillLEDsFromPaletteColors2( astartIndex);
    FillLEDsFromPaletteColors3( astartIndex);
    FillLEDsFromPaletteColors4( astartIndex);
    FillLEDsFromPaletteColors5( astartIndex);
    Serial.println("3-nhanh");
  }
  else if(controlData.buttonState_4 == LOW){
    bpm();
    bpm2();
    bpm3();
    juggle4();
    juggle5();
    Serial.println("4-nhanh");
  }
  else {
    int i;
    for(i=0;i<NUMLEDS_4;i++){
      leds[i] = CRGB::Black;
      leds_2[i] = CRGB::Black;
      leds_3[i] = CRGB::Black;
      leds_4[i] = CRGB::Black;
      leds_5[i] = CRGB::Black;
    }
  }
  FastLED.show();

}

void setup() {
  Serial.begin(921600);
  WiFi.mode(WIFI_STA);  // Chế độ ESP32 nhận
  pinMode(ENVELOPE_PIN, INPUT);
  // FastLED.addLeds<NEOPIXEL, 3>(leds, NUMLEDS);
  // FastLED.addLeds<NEOPIXEL, 5>(twoLeds, NUMLEDS);
  gPal = HeatColors_p;

  for(int i = 0; i <= 255; i++){
    brightness[i] = 0;
    hue[i] = 0;
  }

  //Turn off all the LEDs
  // for(int i=0; i <= NUMLEDS; i++)  
  // {
  // leds[i] = CRGB::Black;
  // twoleds[i] = CRGB::Black;
  // }
 delay( 3000 ); // power-up safety delay
    FastLED.addLeds<LED_TYPE, DATA_PIN, COLOR_ORDER>(leds, NUMLEDS).setCorrection( TypicalLEDStrip );
    FastLED.addLeds<LED_TYPE, DATA_PIN_2, COLOR_ORDER>(leds_2, NUMLEDS_2).setCorrection( TypicalLEDStrip );
    FastLED.addLeds<LED_TYPE, DATA_PIN_3, COLOR_ORDER>(leds_3, NUMLEDS_3).setCorrection( TypicalLEDStrip );
    FastLED.addLeds<LED_TYPE, DATA_PIN_4, COLOR_ORDER>(leds_4, NUMLEDS_4).setCorrection( TypicalLEDStrip );
    FastLED.addLeds<LED_TYPE, DATA_PIN_5, COLOR_ORDER>(leds_5, NUMLEDS_5).setCorrection( TypicalLEDStrip );
    FastLED.setBrightness(  BRIGHTNESS );
    
    currentPalette = RainbowColors_p;
    currentBlending = LINEARBLEND;
  //Update the LED strip
  FastLED.show(); 


  // Khởi tạo FastLED
   

  if (esp_now_init() != ESP_OK) {
    Serial.println("Error initializing ESP-NOW");
    return;
}
  esp_now_register_recv_cb(OnDataRecv);
}
float fscale( float originalMin, float originalMax, float newBegin, float newEnd, float inputValue, float curve){

  float OriginalRange = 0;
  float NewRange = 0;
  float zeroRefCurVal = 0;
  float normalizedCurVal = 0;
  float rangedValue = 0;
  boolean invFlag = 0;


  // condition curve parameter
  // limit range

  if (curve > 10) curve = 10;
  if (curve < -10) curve = -10;

  curve = (curve * -.1) ; // - invert and scale - this seems more intuitive - postive numbers give more weight to high end on output
  curve = pow(10, curve); // convert linear scale into lograthimic exponent for other pow function

  
  // Check for out of range inputValues
  if (inputValue < originalMin) {
    inputValue = originalMin;
  }
  if (inputValue > originalMax) {
    inputValue = originalMax;
  }

  // Zero Refference the values
  OriginalRange = originalMax - originalMin;

  if (newEnd > newBegin){
    NewRange = newEnd - newBegin;
  }
  else
  {
    NewRange = newBegin - newEnd;
    invFlag = 1;
  }

  zeroRefCurVal = inputValue - originalMin;
  normalizedCurVal  =  zeroRefCurVal / OriginalRange;   // normalize to 0 - 1 float

 
  // Check for originalMin > originalMax  - the math for all other cases i.e. negative numbers seems to work out fine
  if (originalMin > originalMax ) {
    return 0;
  }

  if (invFlag == 0){
    rangedValue =  (pow(normalizedCurVal, curve) * NewRange) + newBegin;

  }
  else     // invert the ranges
  { 
    rangedValue =  newBegin - (pow(normalizedCurVal, curve) * NewRange);
  }

  return rangedValue;
  
  }
void loop() {
  uint8_t  i;
  uint16_t minLvl, maxLvl;
  int      n, height;
  // Không có hành động trong vòng lặp chính; dữ liệu được xử lý trong OnDataRecv
}

uint8_t gCurrentPatternNumber = 0; // Index number of which pattern is current
uint8_t gHue = 0; // rotating "base color" used by many of the patterns
  
void rainbow() 
{
   EVERY_N_MILLISECONDS( 20 ) { gHue++; } 
  // FastLED's built-in rainbow generator
  fill_rainbow( leds, NUM_LEDS, gHue, 7);
}

void rainbowWithGlitter() 
{
  // built-in FastLED rainbow, plus some random sparkly glitter
  rainbow();
  addGlitter(80);
}

void addGlitter( fract8 chanceOfGlitter) 
{
  if( random8() < chanceOfGlitter) {
    leds[ random16(NUM_LEDS) ] += CRGB::White;
  }
}
//////////////////


/////////////////////////////////////
#define COOLING  55
#define SPARKING 120
void off(){
  for( int i = 0; i < NUM_LEDS; i++) { //9948
    leds[i] = CRGB::Black;
}}

void bpm()
{
  // colored stripes pulsing at a defined Beats-Per-Minute (BPM)
  // uint8_t  i;
  // uint16_t minLvl, maxLvl;
  // int      n, height;
  uint8_t BeatsPerMinute = 62;
  CRGBPalette16 palette = PartyColors_p;
  uint8_t beat = beatsin8( BeatsPerMinute, 64, 255);
  for( int i = 0; i < NUMLEDS; i++) { //9948
    leds[i] = ColorFromPalette(palette, gHue+(i*2), beat-gHue+(i*10));
  }
}
void bpm2()
{
  // colored stripes pulsing at a defined Beats-Per-Minute (BPM)
  // uint8_t  i;
  // uint16_t minLvl, maxLvl;s
  // int      n, height;
  uint8_t BeatsPerMinute = 62;
  CRGBPalette16 palette = PartyColors_p;
  uint8_t beat = beatsin8( BeatsPerMinute, 64, 255);
  for( int i = 0; i < NUMLEDS_2; i++) { //9948
    leds_2[i] = ColorFromPalette(palette, gHue+(i*2), beat-gHue+(i*10));
  }
}
void bpm3()
{
  // colored stripes pulsing at a defined Beats-Per-Minute (BPM)
  // uint8_t  i;
  // uint16_t minLvl, maxLvl;s
  // int      n, height;
  uint8_t BeatsPerMinute = 62;
  CRGBPalette16 palette = PartyColors_p;
  uint8_t beat = beatsin8( BeatsPerMinute, 64, 255);
  for( int i = 0; i < NUMLEDS_3; i++) { //9948
    leds_3[i] = ColorFromPalette(palette, gHue+(i*2), beat-gHue+(i*10));
  }
}
void bpm4()
{
  // colored stripes pulsing at a defined Beats-Per-Minute (BPM)
  // uint8_t  i;
  // uint16_t minLvl, maxLvl;s
  // int      n, height;
  uint8_t BeatsPerMinute = 62;
  CRGBPalette16 palette = PartyColors_p;
  uint8_t beat = beatsin8( BeatsPerMinute, 64, 255);
  for( int i = 0; i < NUMLEDS_4; i++) { //9948
    leds_4[i] = ColorFromPalette(palette, gHue+(i*2), beat-gHue+(i*10));
  }
}
void bpm5()
{
  // colored stripes pulsing at a defined Beats-Per-Minute (BPM)
  // uint8_t  i;
  // uint16_t minLvl, maxLvl;s
  // int      n, height;
  uint8_t BeatsPerMinute = 62;
  CRGBPalette16 palette = PartyColors_p;
  uint8_t beat = beatsin8( BeatsPerMinute, 64, 255);
  for( int i = 0; i < NUMLEDS_5; i++) { //9948
    leds_5[i] = ColorFromPalette(palette, gHue+(i*2), beat-gHue+(i*10));
  }
}
void LinearReactive(){
 byte val = map(analogVal, 0, SENSITIVITY+1, 0, NUMLEDS);
 byte hue = HUE_INIT;

 for(int i = 0; i <= val; i++){
   leds[i] = CHSV(hue += HUE_CHANGE, SATURATION, MAX_BRIGHTNESS);
 }

 for(int i = val+1; i <= NUMLEDS; i++){
   leds[i].nscale8(5);
 }
}
void ChangePalettePeriodically()
{
    uint8_t secondHand = (millis() / 1000) % 60;
    static uint8_t lastSecond = 99;
    
    if( lastSecond != secondHand) {
        lastSecond = secondHand;
        if( secondHand ==  0)  { currentPalette = RainbowColors_p;         currentBlending = LINEARBLEND; }
        if( secondHand == 10)  { currentPalette = RainbowStripeColors_p;   currentBlending = NOBLEND;  }
        if( secondHand == 15)  { currentPalette = RainbowStripeColors_p;   currentBlending = LINEARBLEND; }
        if( secondHand == 20)  { SetupPurpleAndGreenPalette();             currentBlending = LINEARBLEND; }
        if( secondHand == 25)  { SetupTotallyRandomPalette();              currentBlending = LINEARBLEND; }
        if( secondHand == 30)  { SetupBlackAndWhiteStripedPalette();       currentBlending = NOBLEND; }
        if( secondHand == 35)  { SetupBlackAndWhiteStripedPalette();       currentBlending = LINEARBLEND; }
        if( secondHand == 40)  { currentPalette = CloudColors_p;           currentBlending = LINEARBLEND; }
        if( secondHand == 45)  { currentPalette = PartyColors_p;           currentBlending = LINEARBLEND; }
        if( secondHand == 50)  { currentPalette = myRedWhiteBluePalette_p; currentBlending = NOBLEND;  }
        if( secondHand == 55)  { currentPalette = myRedWhiteBluePalette_p; currentBlending = LINEARBLEND; }
    }
}
void SetupTotallyRandomPalette()
{
    for( int i = 0; i < 16; ++i) {
        currentPalette[i] = CHSV( random8(), 255, random8());
    }
}

// This function sets up a palette of black and white stripes,
// using code.  Since the palette is effectively an array of
// sixteen CRGB colors, the various fill_* functions can be used
// to set them up.
void SetupBlackAndWhiteStripedPalette()
{
    // 'black out' all 16 palette entries...
    fill_solid( currentPalette, 16, CRGB::Black);
    // and set every fourth one to white.
    currentPalette[0] = CRGB::White;
    currentPalette[4] = CRGB::White;
    currentPalette[8] = CRGB::White;
    currentPalette[12] = CRGB::White;
    
}

// This function sets up a palette of purple and green stripes.
void SetupPurpleAndGreenPalette()
{
    CRGB purple = CHSV( HUE_PURPLE, 255, 255);
    CRGB green  = CHSV( HUE_GREEN, 255, 255);
    CRGB black  = CRGB::Black;
    
    currentPalette = CRGBPalette16(
                                   green,  green,  black,  black,
                                   purple, purple, black,  black,
                                   green,  green,  black,  black,
                                   purple, purple, black,  black );
}


// This example shows how to set up a static color palette
// which is stored in PROGMEM (flash), which is almost always more
// plentiful than RAM.  A static PROGMEM palette like this
// takes up 64 bytes of flash.
const TProgmemPalette16 myRedWhiteBluePalette_p PROGMEM =
{
    CRGB::Red,
    CRGB::Gray, // 'white' is too bright compared to red and blue
    CRGB::Blue,
    CRGB::Black,
    
    CRGB::Red,
    CRGB::Gray,
    CRGB::Blue,
    CRGB::Black,
    
    CRGB::Red,
    CRGB::Red,
    CRGB::Gray,
    CRGB::Gray,
    CRGB::Blue,
    CRGB::Blue,
    CRGB::Black,
    CRGB::Black
};
void FillLEDsFromPaletteColors( uint8_t colorIndex)
{
    uint8_t brightness = 255;
    
    for( int i = 0; i < NUMLEDS; ++i) {
        leds[i] = ColorFromPalette( currentPalette, colorIndex, brightness, currentBlending);
        colorIndex += 1;
    }
}
void FillLEDsFromPaletteColors2( uint8_t colorIndex)
{
    uint8_t brightness = 255;
    
    for( int i = 0; i < NUMLEDS_2; ++i) {
        leds_2[i] = ColorFromPalette( currentPalette, colorIndex, brightness, currentBlending);
        colorIndex += 3;
    }
}
void FillLEDsFromPaletteColors3( uint8_t colorIndex)
{
    uint8_t brightness = 255;
    
    for( int i = 0; i < NUMLEDS_3; ++i) {
        leds_3[i] = ColorFromPalette( currentPalette, colorIndex, brightness, currentBlending);
        colorIndex += 3;
    }
}
void FillLEDsFromPaletteColors4( uint8_t colorIndex)
{
    uint8_t brightness = 255;
    
    for( int i = 0; i < NUMLEDS_4; ++i) {
        leds_4[i] = ColorFromPalette( currentPalette, colorIndex, brightness, currentBlending);
        colorIndex += 3;
    }
}
void FillLEDsFromPaletteColors5( uint8_t colorIndex)
{
    uint8_t brightness = 255;
    
    for( int i = 0; i < NUMLEDS_5; ++i) {
        leds_5[i] = ColorFromPalette( currentPalette, colorIndex, brightness, currentBlending);
        colorIndex += 3;
    }
}
void pride() 
{
  static uint16_t sPseudotime = 0;
  static uint16_t sLastMillis = 0;
  static uint16_t sHue16 = 0;
 
  uint8_t sat8 = beatsin88( 87, 220, 250);
  uint8_t brightdepth = beatsin88( 341, 96, 224);
  uint16_t brightnessthetainc16 = beatsin88( 203, (25 * 256), (40 * 256));
  uint8_t msmultiplier = beatsin88(147, 23, 60);

  uint16_t hue16 = sHue16;//gHue * 256;
  uint16_t hueinc16 = beatsin88(113, 1, 3000);
  
  uint16_t ms = millis();
  uint16_t deltams = ms - sLastMillis ;
  sLastMillis  = ms;
  sPseudotime += deltams * msmultiplier;
  sHue16 += deltams * beatsin88( 400, 5,9);
  uint16_t brightnesstheta16 = sPseudotime;
  
  for( uint16_t i = 0 ; i < NUMLEDS; i++) {
    hue16 += hueinc16;
    uint8_t hue8 = hue16 / 256;

    brightnesstheta16  += brightnessthetainc16;
    uint16_t b16 = sin16( brightnesstheta16  ) + 32768;

    uint16_t bri16 = (uint32_t)((uint32_t)b16 * (uint32_t)b16) / 65536;
    uint8_t bri8 = (uint32_t)(((uint32_t)bri16) * brightdepth) / 65536;
    bri8 += (255 - brightdepth);
    
    CRGB newcolor = CHSV( hue8, sat8, bri8);
    
    uint16_t pixelnumber = i;
    pixelnumber = (NUMLEDS-1) - pixelnumber;
    
    nblend( leds[pixelnumber], newcolor, 64);
  }
}
void pride2() 
{
  static uint16_t sPseudotime = 0;
  static uint16_t sLastMillis = 0;
  static uint16_t sHue16 = 0;
 
  uint8_t sat8 = beatsin88( 87, 220, 250);
  uint8_t brightdepth = beatsin88( 341, 96, 224);
  uint16_t brightnessthetainc16 = beatsin88( 203, (25 * 256), (40 * 256));
  uint8_t msmultiplier = beatsin88(147, 23, 60);

  uint16_t hue16 = sHue16;//gHue * 256;
  uint16_t hueinc16 = beatsin88(113, 1, 3000);
  
  uint16_t ms = millis();
  uint16_t deltams = ms - sLastMillis ;
  sLastMillis  = ms;
  sPseudotime += deltams * msmultiplier;
  sHue16 += deltams * beatsin88( 400, 5,9);
  uint16_t brightnesstheta16 = sPseudotime;
  
  for( uint16_t i = 0 ; i < NUMLEDS_2; i++) {
    hue16 += hueinc16;
    uint8_t hue8 = hue16 / 256;

    brightnesstheta16  += brightnessthetainc16;
    uint16_t b16 = sin16( brightnesstheta16  ) + 32768;

    uint16_t bri16 = (uint32_t)((uint32_t)b16 * (uint32_t)b16) / 65536;
    uint8_t bri8 = (uint32_t)(((uint32_t)bri16) * brightdepth) / 65536;
    bri8 += (255 - brightdepth);
    
    CRGB newcolor = CHSV( hue8, sat8, bri8);
    
    uint16_t pixelnumber = i;
    pixelnumber = (NUMLEDS_2-1) - pixelnumber;
    
    nblend( leds_2[pixelnumber], newcolor, 64);
  }
}
void pride3() 
{
  static uint16_t sPseudotime = 0;
  static uint16_t sLastMillis = 0;
  static uint16_t sHue16 = 0;
 
  uint8_t sat8 = beatsin88( 87, 220, 250);
  uint8_t brightdepth = beatsin88( 341, 96, 224);
  uint16_t brightnessthetainc16 = beatsin88( 203, (25 * 256), (40 * 256));
  uint8_t msmultiplier = beatsin88(147, 23, 60);

  uint16_t hue16 = sHue16;//gHue * 256;
  uint16_t hueinc16 = beatsin88(113, 1, 3000);
  
  uint16_t ms = millis();
  uint16_t deltams = ms - sLastMillis ;
  sLastMillis  = ms;
  sPseudotime += deltams * msmultiplier;
  sHue16 += deltams * beatsin88( 400, 5,9);
  uint16_t brightnesstheta16 = sPseudotime;
  
  for( uint16_t i = 0 ; i < NUMLEDS_3; i++) {
    hue16 += hueinc16;
    uint8_t hue8 = hue16 / 256;

    brightnesstheta16  += brightnessthetainc16;
    uint16_t b16 = sin16( brightnesstheta16  ) + 32768;

    uint16_t bri16 = (uint32_t)((uint32_t)b16 * (uint32_t)b16) / 65536;
    uint8_t bri8 = (uint32_t)(((uint32_t)bri16) * brightdepth) / 65536;
    bri8 += (255 - brightdepth);
    
    CRGB newcolor = CHSV( hue8, sat8, bri8);
    
    uint16_t pixelnumber = i;
    pixelnumber = (NUMLEDS_3-1) - pixelnumber;
    
    nblend( leds_3[pixelnumber], newcolor, 64);
  }
}
void pride4() 
{
  static uint16_t sPseudotime = 0;
  static uint16_t sLastMillis = 0;
  static uint16_t sHue16 = 0;
 
  uint8_t sat8 = beatsin88( 87, 220, 250);
  uint8_t brightdepth = beatsin88( 341, 96, 224);
  uint16_t brightnessthetainc16 = beatsin88( 203, (25 * 256), (40 * 256));
  uint8_t msmultiplier = beatsin88(147, 23, 60);

  uint16_t hue16 = sHue16;//gHue * 256;
  uint16_t hueinc16 = beatsin88(113, 1, 3000);
  
  uint16_t ms = millis();
  uint16_t deltams = ms - sLastMillis ;
  sLastMillis  = ms;
  sPseudotime += deltams * msmultiplier;
  sHue16 += deltams * beatsin88( 400, 5,9);
  uint16_t brightnesstheta16 = sPseudotime;
  
  for( uint16_t i = 0 ; i < NUMLEDS_4; i++) {
    hue16 += hueinc16;
    uint8_t hue8 = hue16 / 256;

    brightnesstheta16  += brightnessthetainc16;
    uint16_t b16 = sin16( brightnesstheta16  ) + 32768;

    uint16_t bri16 = (uint32_t)((uint32_t)b16 * (uint32_t)b16) / 65536;
    uint8_t bri8 = (uint32_t)(((uint32_t)bri16) * brightdepth) / 65536;
    bri8 += (255 - brightdepth);
    
    CRGB newcolor = CHSV( hue8, sat8, bri8);
    
    uint16_t pixelnumber = i;
    pixelnumber = (NUMLEDS_4-1) - pixelnumber;
    
    nblend( leds_4[pixelnumber], newcolor, 64);
  }
}
void pride5() 
{
  static uint16_t sPseudotime = 0;
  static uint16_t sLastMillis = 0;
  static uint16_t sHue16 = 0;
 
  uint8_t sat8 = beatsin88( 87, 220, 250);
  uint8_t brightdepth = beatsin88( 341, 96, 224);
  uint16_t brightnessthetainc16 = beatsin88( 203, (25 * 256), (40 * 256));
  uint8_t msmultiplier = beatsin88(147, 23, 60);

  uint16_t hue16 = sHue16;//gHue * 256;
  uint16_t hueinc16 = beatsin88(113, 1, 3000);
  
  uint16_t ms = millis();
  uint16_t deltams = ms - sLastMillis ;
  sLastMillis  = ms;
  sPseudotime += deltams * msmultiplier;
  sHue16 += deltams * beatsin88( 400, 5,9);
  uint16_t brightnesstheta16 = sPseudotime;
  
  for( uint16_t i = 0 ; i < NUMLEDS_5; i++) {
    hue16 += hueinc16;
    uint8_t hue8 = hue16 / 256;

    brightnesstheta16  += brightnessthetainc16;
    uint16_t b16 = sin16( brightnesstheta16  ) + 32768;

    uint16_t bri16 = (uint32_t)((uint32_t)b16 * (uint32_t)b16) / 65536;
    uint8_t bri8 = (uint32_t)(((uint32_t)bri16) * brightdepth) / 65536;
    bri8 += (255 - brightdepth);
    
    CRGB newcolor = CHSV( hue8, sat8, bri8);
    
    uint16_t pixelnumber = i;
    pixelnumber = (NUMLEDS_2-1) - pixelnumber;
    
    nblend( leds_5[pixelnumber], newcolor, 64);
  }
}
void juggle() {
  // eight colored dots, weaving in and out of sync with each other
  fadeToBlackBy( leds, NUMLEDS, 20);
  uint8_t dothue = 0;
  for( int i = 0; i < 8; i++) {
    leds[beatsin16( i+7, 0, NUMLEDS-1 )] |= CHSV(dothue, 200, 255);
    dothue += 32;
  }}
  void juggle2() {
  // eight colored dots, weaving in and out of sync with each other
  fadeToBlackBy( leds_2, NUMLEDS_2, 20);
  uint8_t dothue = 0;
  for( int i = 0; i < 8; i++) {
    leds_2[beatsin16( i+7, 0, NUMLEDS_2-1 )] |= CHSV(dothue, 200, 255);
    dothue += 32;
  }}
    void juggle3() {
  // eight colored dots, weaving in and out of sync with each other
  fadeToBlackBy( leds_3, NUMLEDS_3, 20);
  uint8_t dothue = 0;
  for( int i = 0; i < 8; i++) {
    leds_3[beatsin16( i+7, 0, NUMLEDS_3-1 )] |= CHSV(dothue, 200, 255);
    dothue += 32;
  }}
    void juggle4() {
  // eight colored dots, weaving in and out of sync with each other
  fadeToBlackBy( leds_4, NUMLEDS_4, 20);
  uint8_t dothue = 0;
  for( int i = 0; i < 8; i++) {
    leds_4[beatsin16( i+7, 0, NUMLEDS_4-1 )] |= CHSV(dothue, 200, 255);
    dothue += 32;
  }}
    void juggle5() {
  // eight colored dots, weaving in and out of sync with each other
  fadeToBlackBy( leds_5, NUMLEDS_5, 20);
  uint8_t dothue = 0;
  for( int i = 0; i < 8; i++) {
    leds_5[beatsin16( i+7, 0, NUMLEDS_5-1 )] |= CHSV(dothue, 200, 255);
    dothue += 32;
  }}
  void confetti() 
{
  // random colored speckles that blink in and fade smoothly
  fadeToBlackBy( leds, NUMLEDS, 100);
  int pos = random16(NUMLEDS);
  leds[pos] += CHSV( gHue + random8(255), 200, 255);
}
void confetti2() 
{
  // random colored speckles that blink in and fade smoothly
  fadeToBlackBy( leds_2, NUMLEDS_2, 100);
  int pos = random16(NUMLEDS_2);
  leds_2[pos] += CHSV( gHue + random8(255), 200, 255);
}
void confetti3() 
{
  // random colored speckles that blink in and fade smoothly
  fadeToBlackBy( leds_3, NUMLEDS_3, 100);
  int pos = random16(NUMLEDS_3);
  leds_3[pos] += CHSV( gHue + random8(255), 200, 255);
}
void confetti4() 
{
  // random colored speckles that blink in and fade smoothly
  fadeToBlackBy( leds_4, NUMLEDS_4, 100);
  int pos = random16(NUMLEDS_4);
  leds_2[pos] += CHSV( gHue + random8(255), 200, 255);
}
void confetti5() 
{
  // random colored speckles that blink in and fade smoothly
  fadeToBlackBy( leds_5, NUMLEDS_5, 100);
  int pos = random16(NUMLEDS_5);
  leds_5[pos] += CHSV( gHue + random8(255), 200, 255);
}
void sinelon()
{
  // a colored dot sweeping back and forth, with fading trails
  fadeToBlackBy( leds, NUMLEDS, 20);
  int pos = beatsin16( 13, 0, NUMLEDS-1 );
  leds[pos] += CHSV( gHue+ random(100), 255, 192);
}
void sinelon2()
{
  // a colored dot sweeping back and forth, with fading trails
  fadeToBlackBy( leds_2, NUMLEDS_2, 20);
  int pos = beatsin16( 13, 0, NUMLEDS_2-1 );
  leds_2[pos] += CHSV( gHue+ random(100), 255, 192);
}
void sinelon3()
{
  // a colored dot sweeping back and forth, with fading trails
  fadeToBlackBy( leds_3, NUMLEDS_3, 20);
  int pos = beatsin16( 13, 0, NUMLEDS_3-1 );
  leds_3[pos] += CHSV( gHue+ random(100), 255, 192);
}
void sinelon4()
{
  // a colored dot sweeping back and forth, with fading trails
  fadeToBlackBy( leds_4, NUMLEDS_4, 20);
  int pos = beatsin16( 13, 0, NUMLEDS_4-1 );
  leds_4[pos] += CHSV( gHue+ random(100), 255, 192);
}
void sinelon5()
{
  // a colored dot sweeping back and forth, with fading trails
  fadeToBlackBy( leds_5, NUMLEDS_5, 20);
  int pos = beatsin16( 13, 0, NUMLEDS_5-1 );
  leds_5[pos] += CHSV( gHue+ random(100), 255, 192);
}
void Fire2012WithPalette()
{
// Array of temperature readings at each simulation cell
  static uint8_t heat[NUMLEDS];

  // Step 1.  Cool down every cell a little
    for( int i = 0; i < NUMLEDS; i++) {
      heat[i] = qsub8( heat[i],  random8(0, ((COOLING * 10) / NUMLEDS) + 2));
    }
  
    // Step 2.  Heat from each cell drifts 'up' and diffuses a little
    for( int k= NUMLEDS - 1; k >= 2; k--) {
      heat[k] = (heat[k - 1] + heat[k - 2] + heat[k - 2] ) / 3;
    }
    
    // Step 3.  Randomly ignite new 'sparks' of heat near the bottom
    if( random8() < SPARKING ) {
      int y = random8(7);
      heat[y] = qadd8( heat[y], random8(20,160) );
    }

    // Step 4.  Map from heat cells to LED colors
    for( int j = 0; j < NUMLEDS; j++) {
      // Scale the heat value from 0-255 down to 0-240
      // for best results with color palettes.
      uint8_t colorindex = scale8( heat[j], 150);
      CRGB color = ColorFromPalette( gPal, colorindex);
      int pixelnumber;
      if( gReverseDirection ) {
        pixelnumber = (NUMLEDS-1) - j;
      } else {
        pixelnumber = j;
      }
      leds[pixelnumber] = color;
    }
}
void Fire2012WithPalette2()
{
// Array of temperature readings at each simulation cell
  static uint8_t heat[NUMLEDS_2];

  // Step 1.  Cool down every cell a little
    for( int i = 0; i < NUMLEDS_2; i++) {
      heat[i] = qsub8( heat[i],  random8(0, ((COOLING * 10) / NUMLEDS_2) + 2));
    }
  
    // Step 2.  Heat from each cell drifts 'up' and diffuses a little
    for( int k= NUMLEDS_2 - 1; k >= 2; k--) {
      heat[k] = (heat[k - 1] + heat[k - 2] + heat[k - 2] ) / 3;
    }
    
    // Step 3.  Randomly ignite new 'sparks' of heat near the bottom
    if( random8() < SPARKING ) {
      int y = random8(7);
      heat[y] = qadd8( heat[y], random8(160,255) );
    }

    // Step 4.  Map from heat cells to LED colors
    for( int j = 0; j < NUMLEDS_2; j++) {
      // Scale the heat value from 0-255 down to 0-240
      // for best results with color palettes.
      uint8_t colorindex = scale8( heat[j], 240);
      CRGB color = ColorFromPalette( gPal, colorindex);
      int pixelnumber;
      if( gReverseDirection ) {
        pixelnumber = (NUMLEDS_2-1) - j;
      } else {
        pixelnumber = j;
      }
      leds_2[pixelnumber] = color;
    }
}
void Fire2012WithPalette3()
{
// Array of temperature readings at each simulation cell
  static uint8_t heat[NUMLEDS_3];

  // Step 1.  Cool down every cell a little
    for( int i = 0; i < NUMLEDS_3; i++) {
      heat[i] = qsub8( heat[i],  random8(0, ((COOLING * 10) / NUMLEDS_3) + 2));
    }
  
    // Step 2.  Heat from each cell drifts 'up' and diffuses a little
    for( int k= NUMLEDS_3 - 1; k >= 2; k--) {
      heat[k] = (heat[k - 1] + heat[k - 2] + heat[k - 2] ) / 3;
    }
    
    // Step 3.  Randomly ignite new 'sparks' of heat near the bottom
    if( random8() < SPARKING ) {
      int y = random8(7);
      heat[y] = qadd8( heat[y], random8(160,255) );
    }

    // Step 4.  Map from heat cells to LED colors
    for( int j = 0; j < NUMLEDS_3; j++) {
      // Scale the heat value from 0-255 down to 0-240
      // for best results with color palettes.
      uint8_t colorindex = scale8( heat[j], 240);
      CRGB color = ColorFromPalette( gPal, colorindex);
      int pixelnumber;
      if( gReverseDirection ) {
        pixelnumber = (NUMLEDS_3-1) - j;
      } else {
        pixelnumber = j;
      }
      leds_3[pixelnumber] = color;
    }
}
void Fire2012WithPalette4()
{
// Array of temperature readings at each simulation cell
  static uint8_t heat[NUMLEDS_4];

  // Step 1.  Cool down every cell a little
    for( int i = 0; i < NUMLEDS_4; i++) {
      heat[i] = qsub8( heat[i],  random8(0, ((COOLING * 10) / NUMLEDS_4) + 2));
    }
  
    // Step 2.  Heat from each cell drifts 'up' and diffuses a little
    for( int k= NUMLEDS_4 - 1; k >= 2; k--) {
      heat[k] = (heat[k - 1] + heat[k - 2] + heat[k - 2] ) / 3;
    }
    
    // Step 3.  Randomly ignite new 'sparks' of heat near the bottom
    if( random8() < SPARKING ) {
      int y = random8(7);
      heat[y] = qadd8( heat[y], random8(160,255) );
    }

    // Step 4.  Map from heat cells to LED colors
    for( int j = 0; j < NUMLEDS_4; j++) {
      // Scale the heat value from 0-255 down to 0-240
      // for best results with color palettes.
      uint8_t colorindex = scale8( heat[j], 240);
      CRGB color = ColorFromPalette( gPal, colorindex);
      int pixelnumber;
      if( gReverseDirection ) {
        pixelnumber = (NUMLEDS_4-1) - j;
      } else {
        pixelnumber = j;
      }
      leds_4[pixelnumber] = color;
    }
}
void Fire2012WithPalette5()
{
// Array of temperature readings at each simulation cell
  static uint8_t heat[NUMLEDS_5];

  // Step 1.  Cool down every cell a little
    for( int i = 0; i < NUMLEDS_5; i++) {
      heat[i] = qsub8( heat[i],  random8(0, ((COOLING * 10) / NUMLEDS_5) + 2));
    }
  
    // Step 2.  Heat from each cell drifts 'up' and diffuses a little
    for( int k= NUMLEDS_5 - 1; k >= 2; k--) {
      heat[k] = (heat[k - 1] + heat[k - 2] + heat[k - 2] ) / 3;
    }
    
    // Step 3.  Randomly ignite new 'sparks' of heat near the bottom
    if( random8() < SPARKING ) {
      int y = random8(7);
      heat[y] = qadd8( heat[y], random8(160,255) );
    }

    // Step 4.  Map from heat cells to LED colors
    for( int j = 0; j < NUMLEDS_5; j++) {
      // Scale the heat value from 0-255 down to 0-240
      // for best results with color palettes.
      uint8_t colorindex = scale8( heat[j], 240);
      CRGB color = ColorFromPalette( gPal, colorindex);
      int pixelnumber;
      if( gReverseDirection ) {
        pixelnumber = (NUMLEDS_5-1) - j;
      } else {
        pixelnumber = j;
      }
      leds_5[pixelnumber] = color;
    }
}
void Espl2SDemo(){
  uint32_t ms = millis();

    for (int i = 0; i < NUMLEDS; i++) {
        // Sử dụng noise để tính toán giá trị cho mỗi LED
        uint8_t hue = inoise16(ms * 10, i * 3000, 0) >> 8;
        uint8_t sat = inoise16(ms * 15, i * 1500, 1000) >> 8;
        uint8_t val = inoise16(ms * 20, i * 500, 2000) >> 8;

        // Điều chỉnh biên độ noise
        sat = map(sat, 0, 255, 100, 255); // Độ bão hòa cao hơn
        val = map(val, 0, 255, 50, 255); // Giá trị sáng từ nhấp nháy nhẹ đến sáng hẳn

        // Áp dụng hiệu ứng sóng chảy dọc theo dải LED
        uint8_t wave = sin8(ms / 10 + i * 20); 
        hue += wave / 5; // Điều chỉnh màu theo sóng
        
        // Đặt giá trị LED
        leds[i] = CHSV(hue, sat, val);
    }

    // Làm mờ dần dải LED để thêm hiệu ứng chuyển đổi mượt mà
    fadeToBlackBy(leds, NUMLEDS, 10);

}
void Espl2SDemo2(){
  uint32_t ms = millis();

    for (int i = 0; i < NUMLEDS_2; i++) {
        // Sử dụng noise để tính toán giá trị cho mỗi LED
        uint8_t hue = inoise16(ms * 10, i * 3000, 0) >> 8;
        uint8_t sat = inoise16(ms * 15, i * 1500, 1000) >> 8;
        uint8_t val = inoise16(ms * 20, i * 500, 2000) >> 8;

        // Điều chỉnh biên độ noise
        sat = map(sat, 0, 255, 100, 255); // Độ bão hòa cao hơn
        val = map(val, 0, 255, 50, 255); // Giá trị sáng từ nhấp nháy nhẹ đến sáng hẳn

        // Áp dụng hiệu ứng sóng chảy dọc theo dải LED
        uint8_t wave = sin8(ms / 10 + i * 20); 
        hue += wave / 5; // Điều chỉnh màu theo sóng
        
        // Đặt giá trị LED
        leds_2[i] = CHSV(hue, sat, val);
    }

    // Làm mờ dần dải LED để thêm hiệu ứng chuyển đổi mượt mà
    fadeToBlackBy(leds_2, NUMLEDS_2, 10);

}
void Espl2SDemo3(){
  
    uint32_t ms = millis();

    for (int i = 0; i < NUMLEDS_3; i++) {
        // Sử dụng noise để tính toán giá trị cho mỗi LED
        uint8_t hue = inoise16(ms * 10, i * 3000, 0) >> 8;
        uint8_t sat = inoise16(ms * 15, i * 1500, 1000) >> 8;
        uint8_t val = inoise16(ms * 20, i * 500, 2000) >> 8;

        // Điều chỉnh biên độ noise
        sat = map(sat, 0, 255, 100, 255); // Độ bão hòa cao hơn
        val = map(val, 0, 255, 50, 255); // Giá trị sáng từ nhấp nháy nhẹ đến sáng hẳn

        // Áp dụng hiệu ứng sóng chảy dọc theo dải LED
        uint8_t wave = sin8(ms / 10 + i * 20); 
        hue += wave / 5; // Điều chỉnh màu theo sóng
        
        // Đặt giá trị LED
        leds_3[i] = CHSV(hue, sat, val);
    }

    // Làm mờ dần dải LED để thêm hiệu ứng chuyển đổi mượt mà
    fadeToBlackBy(leds_3, NUMLEDS_3, 10);

}
void Espl2SDemo4(){
  uint32_t ms = millis();

    for (int i = 0; i < NUMLEDS_4; i++) {
        // Sử dụng noise để tính toán giá trị cho mỗi LED
        uint8_t hue = inoise16(ms * 10, i * 3000, 0) >> 8;
        uint8_t sat = inoise16(ms * 15, i * 1500, 1000) >> 8;
        uint8_t val = inoise16(ms * 20, i * 500, 2000) >> 8;

        // Điều chỉnh biên độ noise
        sat = map(sat, 0, 255, 100, 255); // Độ bão hòa cao hơn
        val = map(val, 0, 255, 50, 255); // Giá trị sáng từ nhấp nháy nhẹ đến sáng hẳn

        // Áp dụng hiệu ứng sóng chảy dọc theo dải LED
        uint8_t wave = sin8(ms / 10 + i * 20); 
        hue += wave / 5; // Điều chỉnh màu theo sóng
        
        // Đặt giá trị LED
        leds_4[i] = CHSV(hue, sat, val);
    }

    // Làm mờ dần dải LED để thêm hiệu ứng chuyển đổi mượt mà
    fadeToBlackBy(leds_4, NUMLEDS_4, 10);

}
void Espl2SDemo5(){
  uint32_t ms = millis();

    for (int i = 0; i < NUMLEDS_5; i++) {
        // Sử dụng noise để tính toán giá trị cho mỗi LED
        uint8_t hue = inoise16(ms * 10, i * 3000, 0) >> 8;
        uint8_t sat = inoise16(ms * 15, i * 1500, 1000) >> 8;
        uint8_t val = inoise16(ms * 20, i * 500, 2000) >> 8;

        // Điều chỉnh biên độ noise
        sat = map(sat, 0, 255, 100, 255); // Độ bão hòa cao hơn
        val = map(val, 0, 255, 50, 255); // Giá trị sáng từ nhấp nháy nhẹ đến sáng hẳn

        // Áp dụng hiệu ứng sóng chảy dọc theo dải LED
        uint8_t wave = sin8(ms / 10 + i * 20); 
        hue += wave / 5; // Điều chỉnh màu theo sóng
        
        // Đặt giá trị LED
        leds_5[i] = CHSV(hue, sat, val);
    }

    // Làm mờ dần dải LED để thêm hiệu ứng chuyển đổi mượt mà
    fadeToBlackBy(leds_5, NUMLEDS_5, 10);

 }
void ColorTemperatureEx(){
  static uint8_t starthue = 0;
  fill_rainbow( leds , NUMLEDS , --starthue, 20);
  // fill_rainbow( leds_2 , NUMLEDS , --starthue, 20);
  // fill_rainbow( leds_3 , NUMLEDS , --starthue, 20);
  // fill_rainbow( leds_4 , NUMLEDS , --starthue, 20);
  // fill_rainbow( leds_5 , NUMLEDS , --starthue, 20);
  // Choose which 'color temperature' profile to enable.
  uint8_t secs = (millis() / 1000) % (DISPLAYTIME * 2);
  if( secs < DISPLAYTIME) {
    FastLED.setTemperature( TEMPERATURE_1 ); // first temperature
  } else {
    FastLED.setTemperature( TEMPERATURE_2 ); // second temperature
  }
 
}
void ColorTemperatureEx2(){
  static uint8_t starthue = 0;
  fill_rainbow( leds_2 , NUMLEDS , --starthue, 20);
 
  // Choose which 'color temperature' profile to enable.
  uint8_t secs = (millis() / 1000) % (DISPLAYTIME * 2);
  if( secs < DISPLAYTIME) {
    FastLED.setTemperature( TEMPERATURE_1 ); // first temperature
  } else {
    FastLED.setTemperature( TEMPERATURE_2 ); // second temperature
  }
 
  
}
void ColorTemperatureEx3(){
  static uint8_t starthue = 0;
  fill_rainbow( leds_3, NUMLEDS , --starthue, 20);
 
  // Choose which 'color temperature' profile to enable.
  uint8_t secs = (millis() / 1000) % (DISPLAYTIME * 2);
  if( secs < DISPLAYTIME) {
    FastLED.setTemperature( TEMPERATURE_1 ); // first temperature
  } else {
    FastLED.setTemperature( TEMPERATURE_2 ); // second temperature
  }
 
  
}
void ColorTemperatureEx4(){
  static uint8_t starthue = 0;
  fill_rainbow( leds_4 , NUMLEDS , --starthue, 20);
 
  // Choose which 'color temperature' profile to enable.
  uint8_t secs = (millis() / 1000) % (DISPLAYTIME * 2);
  if( secs < DISPLAYTIME) {
    FastLED.setTemperature( TEMPERATURE_1 ); // first temperature
  } else {
    FastLED.setTemperature( TEMPERATURE_2 ); // second temperature
  }
 
  
}
void ColorTemperatureEx5(){
  static uint8_t starthue = 0;
  fill_rainbow( leds_5 , NUMLEDS , --starthue, 20);
 
  // Choose which 'color temperature' profile to enable.
  uint8_t secs = (millis() / 1000) % (DISPLAYTIME * 2);
  if( secs < DISPLAYTIME) {
    FastLED.setTemperature( TEMPERATURE_1 ); // first temperature
  } else {
    FastLED.setTemperature( TEMPERATURE_2 ); // second temperature
  }
}
void rainbowCycle(int SpeedDelay) {
  for (int j = 0; j < 256 ; j++) { // 5 chu kỳ của tất cả các màu trên bánh xe màu
    for (int i = 0; i < NUMLEDS; i++) {
      CRGB color = Wheel(((i * 256 / NUMLEDS) + j) & 255);
      leds[i] = color;
      leds_2[i] = color;
      leds_3[i] = color;
      leds_4[i] = color;
      leds_5[i] = color;
    }
    // delay(SpeedDelay);
  }
}

// Hàm Wheel để tính toán màu sắc cầu vồng
CRGB Wheel(byte WheelPos) {
  byte r, g, b;

  if (WheelPos < 85) {
    r = WheelPos * 3;
    g = 255 - WheelPos * 3;
    b = 0;
  } else if (WheelPos < 170) {
    WheelPos -= 85;
    r = 255 - WheelPos * 3;
    g = 0;
    b = WheelPos * 3;
  } else {
    WheelPos -= 170;
    r = 0;
    g = WheelPos * 3;
    b = 255 - WheelPos * 3;
  }

  return CRGB(r, g, b);
}
