//*******************************includes********************************
#include <LiquidCrystal.h>
#include <SoftwareSerial.h>
#include <Adafruit_Fingerprint.h>
//************************************************************************
const int rs = 5, en = 6, d4 = 10, d5 = 11, d6 = 12, d7 = 13, rst = 9, enr = 4;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);
SoftwareSerial fpSerial(2, 3); // rx , tx
SoftwareSerial EspSerial(7, 8); // rx , tx 

Adafruit_Fingerprint finger = Adafruit_Fingerprint(&fpSerial);

uint8_t id;
String Name;

void setup()
{
  pinMode(enr, INPUT_PULLUP);
  pinMode(rst, INPUT_PULLUP);
  
  // Initialize lcd
  lcd.begin(24,2);
  Serial.begin(9600);
  Serial.println("Welcome to IoT Attendance System");
  lcd.print("Welcome to IoT");
  lcd.setCursor(0,1);
  lcd.print("Attendance System");
  delay(1000);
  lcd.clear();

  // Initialize ESP Serial
  EspSerial.begin(115200);
  
  // Initialize FP Sensor
  finger.begin(57600);

  if (finger.verifyPassword()) {
    Serial.println("Found fingerprint sensor");
    lcd.print("Found fingerprint sensor");
    
  } else {
    Serial.println("Did not find fingerprint sensor :(");
    lcd.print("Did not find fingerprint");
    lcd.setCursor(0,1);
    lcd.print("sensor");
    while (1) { delay(1); }
  }

  Serial.println("Done");
  lcd.setCursor(0, 1);
  lcd.print("Done");
  delay(5000);
  lcd.clear();
  
}

uint8_t readnumber(void) {
  uint8_t num = 0;

  while (num == 0) {
    while (! Serial.available());
    num = Serial.parseInt();
  }
  return num;
}

uint8_t getFingerprintEnroll() {
  // 1st Step
  int p = -1;
  Serial.print("Waiting for valid finger to enroll as #");
  Serial.println(id);
  lcd.print("Waiting for valid finger");
  lcd.setCursor(0, 1);
  lcd.print("to enroll as #");
  lcd.setCursor(15,1);
  lcd.print(id);
  delay(1000);
  lcd.clear();

  while (p != FINGERPRINT_OK) {
    p = finger.getImage();
    switch (p) {
    case FINGERPRINT_OK:
      Serial.println("Image taken");
      lcd.print("Image taken");
      delay(1000);
      lcd.clear();
      
      break;
    case FINGERPRINT_NOFINGER:
      break;
    case FINGERPRINT_PACKETRECIEVEERR:
      Serial.println("Communication error");
      lcd.print("Communication error");
      delay(1000);
      lcd.clear();
      
      break;
    case FINGERPRINT_IMAGEFAIL:
      Serial.println("Imaging error");
      lcd.print("Imaging error");
      delay(1000);
      lcd.clear();

      break;
    default:
      Serial.println("Unknown error");
      lcd.print("Unknown error");
      delay(1000);
      lcd.clear();
      
      break;
    }
  }

  // 2nd Step
  p = finger.image2Tz(1);
  switch (p) {
    case FINGERPRINT_OK:
      Serial.println("Image converted");
      lcd.print("Image converted");
      delay(1000);
      lcd.clear();
      
      break;
    case FINGERPRINT_IMAGEMESS:
      Serial.println("Image too messy");
      lcd.print("Image too messy");
      delay(1000);
      lcd.clear();
      
      return p;
    case FINGERPRINT_PACKETRECIEVEERR:
      Serial.println("Communication error");
      lcd.print("Communication error");
      
      return p;
    case FINGERPRINT_FEATUREFAIL:
      Serial.println("Could not find fingerprint features");
      lcd.print("Could not find");
      lcd.setCursor(0, 1);
      lcd.print("fingerprint features");
      delay(1000);
      lcd.clear();
      
      return p;
    case FINGERPRINT_INVALIDIMAGE:
      Serial.println("Could not find fingerprint features");
      lcd.print("Could not find");
      lcd.setCursor(0, 1);
      lcd.print("fingerprint features");
      delay(1000);
      lcd.clear();
      
      return p;
    default:
      Serial.println("Unknown error");
      lcd.print("Unknown error");
      delay(1000);
      lcd.clear();
      
      return p;
  }

  Serial.println("Remove finger");
  lcd.print("Remove finger");
  delay(2000);
  lcd.clear();

  p = 0;
  while (p != FINGERPRINT_NOFINGER) {
    p = finger.getImage();
  }

  Serial.print("ID ");
  Serial.println(id);
  lcd.print("ID ");
  lcd.setCursor(4, 0);
  lcd.print(id);
  delay(1000);
  lcd.clear();
  

  // 3rd Step
  p = -1;
  Serial.println("Place same finger again");
  lcd.print("Place same finger again");
  delay(1000);
  lcd.clear();
  while (p != FINGERPRINT_OK) {
    p = finger.getImage();
    switch (p) {
    case FINGERPRINT_OK:
      Serial.println("Image taken");
      lcd.print("Image taken");
      delay(1000);
      lcd.clear();
      
      break;
    case FINGERPRINT_NOFINGER:
      break;
    case FINGERPRINT_PACKETRECIEVEERR:
      Serial.println("Communication error");
      lcd.print("Communication error");
      delay(1000);
      lcd.clear();

      break;
    case FINGERPRINT_IMAGEFAIL:
      Serial.println("Imaging error");
      lcd.print("Imaging error");
      delay(1000);
      lcd.clear();

      break;
    default:
      Serial.println("Unknown error");
      lcd.print("Unknown error");
      delay(1000);
      lcd.clear();

      break;
    }
  }

  // 4th Step
  p = finger.image2Tz(2);
  switch (p) {
    case FINGERPRINT_OK:
      Serial.println("Image converted");
      lcd.print("Image converted");
      delay(1000);
      lcd.clear();

      break;
    case FINGERPRINT_IMAGEMESS:
      Serial.println("Image too messy");
      lcd.print("Image too messy");
      delay(1000);
      lcd.clear();

      return p;
    case FINGERPRINT_PACKETRECIEVEERR:
      Serial.println("Communication error");
      lcd.print("Communication error");
      delay(1000);
      lcd.clear();

      return p;
    case FINGERPRINT_FEATUREFAIL:
      Serial.println("Could not find fingerprint features");
      lcd.print("Could not find");
      lcd.setCursor(0, 1);
      lcd.print("fingerprint features");
      delay(1000);
      lcd.clear();

      return p;
    case FINGERPRINT_INVALIDIMAGE:
      Serial.println("Could not find fingerprint features");
      lcd.print("Could not find");
      lcd.setCursor(0, 1);
      lcd.print("fingerprint features");
      delay(1000);
      lcd.clear();

      return p;
    default:
      Serial.println("Unknown error");
      lcd.print("Unknown error");
      delay(1000);
      lcd.clear();

      return p;
  }

  // 5th Step
  Serial.print("Creating model for #");
  Serial.println(id);
  lcd.print("Creating model for #");
  lcd.setCursor(21, 0);
  lcd.print(id);
  delay(1000);
  lcd.clear();  

  p = finger.createModel();
  if (p == FINGERPRINT_OK) {
    Serial.println("Prints matched!");
    lcd.print("Prints matched!");
    delay(1000);
    lcd.clear();

  } else if (p == FINGERPRINT_PACKETRECIEVEERR) {
    Serial.println("Communication error");
    lcd.print("Communication error");
    delay(1000);
    lcd.clear();

    return p;
  } else if (p == FINGERPRINT_ENROLLMISMATCH) {
    Serial.println("Fingerprints did not match");
    lcd.print("Fingerprints did not");
    lcd.setCursor(0, 1);
    lcd.print("match");
    delay(1000);
    lcd.clear();

    return p;
  } else {
    Serial.println("Unknown error");
    lcd.print("Unknown error");
    delay(1000);
    lcd.clear();

    return p;
  }

  Serial.print("ID ");
  Serial.println(id);
  lcd.print("ID ");
  lcd.setCursor(4, 0);
  lcd.print(id);
  EspSerial.print(id);
  delay(1000);
  lcd.clear();

  p = finger.storeModel(id);
  if (p == FINGERPRINT_OK) {
    Serial.println("Stored!");
    lcd.print("Stored!");
    delay(1000);
    lcd.clear();

  } else if (p == FINGERPRINT_PACKETRECIEVEERR) {
    Serial.println("Communication error");
    lcd.print("Communication error");
    delay(1000);
    lcd.clear();

    return p;
  } else if (p == FINGERPRINT_BADLOCATION) {
    Serial.println("Could not store in that location");
    lcd.print("Could not store in that");
    lcd.setCursor(0, 1);
    lcd.print("location");
    delay(1000);
    lcd.clear();

    return p;
  } else if (p == FINGERPRINT_FLASHERR) {
    Serial.println("Error writing to flash");
    lcd.print("Error writing to flash");
    delay(1000);
    lcd.clear();

    return p;
  } else {
    Serial.println("Unknown error");
    lcd.print("Unknown error");
    delay(1000);
    lcd.clear();

    return p;
  }
}

uint8_t deleteFingerprint(uint8_t idd) {
  
  uint8_t p = -1;
  p = finger.deleteModel(idd);

  if (p == FINGERPRINT_OK) {
    Serial.println("Deleted!");
    lcd.print("Deleted!");
    delay(1000);
    lcd.clear();

  } else if (p == FINGERPRINT_PACKETRECIEVEERR) {
    Serial.println("Communication error");
  } else if (p == FINGERPRINT_BADLOCATION) {
    Serial.println("Could not delete in that location");
  } else if (p == FINGERPRINT_FLASHERR) {
    Serial.println("Error writing to flash");
  } else {
    Serial.print("Unknown error: 0x");
    Serial.println(p, HEX);
    lcd.print("Unknown error: 0x");
    lcd.setCursor(18, 0);
    lcd.print(p, HEX);
    delay(1000);
    lcd.clear();
  }

  return p;
}

void loop()
{
  if ( (digitalRead(rst) == LOW) && !(digitalRead(enr) == LOW) ) {
    // Reset DATABASE
    Serial.println("\n\nDeleting all fingerprint templates!");
    lcd.print("Deleting all fingerprint");
    lcd.setCursor(0,1);
    lcd.print("templates!");
    delay(2000);
    lcd.clear();
    finger.emptyDatabase();
    Serial.println("Now database is empty :)");
    lcd.print("Now database is empty");
    id = 0;
    delay(2000);
    lcd.clear();

  } else if ( (digitalRead(enr) == LOW) && !(digitalRead(rst)  == LOW) ) {
    // Enroll FingerPrint
    id++;
    Serial.println("Ready to enroll a fingerprint!");
    lcd.print("Ready to enroll a");
    lcd.setCursor(0,1);
    lcd.print("fingerprint!");
    delay(1000);
    lcd.clear();

    Serial.print("Enrolling ID #");
    Serial.println(id);
    lcd.print("Enrolling ID #");
    lcd.setCursor(15,0);
    lcd.print(id);
    delay(1000);
    lcd.clear();

    while ( !  getFingerprintEnroll() );

  } else if ( (digitalRead(enr) == LOW) && (digitalRead(rst) == LOW) ) {
    // Delete FP by ID
    uint8_t idd = 0;
    Serial.println("\n\nDeleting fingerprint by ID");
    lcd.print("Deleting fingerprint by ID");
    delay(2000);
    lcd.clear();
    Serial.println("Please type in the ID # (from 1 to 127) you want to delete...");
    lcd.print("Please type the ID you");
    lcd.setCursor(0, 1);
    lcd.print("want to delete in serial");
    idd = readnumber();
    if (idd == 0) {// ID #0 not allowed
      return;
    }

    delay(1000);
    lcd.clear();
    Serial.print("Deleting ID #");
    Serial.println(idd);
    lcd.print("Deleting ID #");
    lcd.setCursor(14, 0);
    lcd.print(idd);
    delay(1000);
    lcd.clear();

    deleteFingerprint(idd);

  } else {
    Serial.println("Please Place your Finger");
    lcd.print("Please Place your Finger");
    getFingerprintID();
    delay(1000);
    lcd.clear();
  }
}

uint8_t getFingerprintID() {
  uint8_t p = finger.getImage();
    switch (p) {
    case FINGERPRINT_OK:
      Serial.println("Image taken");
      lcd.print("Image taken");
      delay(1000);
      lcd.clear();

      break;
    case FINGERPRINT_NOFINGER:
      break;
    case FINGERPRINT_PACKETRECIEVEERR:
      Serial.println("Communication error");
      lcd.print("Communication error");
      delay(1000);
      lcd.clear();

      break;
    case FINGERPRINT_IMAGEFAIL:
      Serial.println("Imaging error");
      lcd.print("Imaging error");
      delay(1000);
      lcd.clear();

      break;
    default:
      Serial.println("Unknown error");
      lcd.print("Unknown error");
      delay(1000);
      lcd.clear();

      break;
    }

  // OK success!

  p = finger.image2Tz();
  switch (p) {
    case FINGERPRINT_OK:
      Serial.println("Image converted");
      lcd.print("Image converted");
      delay(1000);
      lcd.clear();

      break;
    case FINGERPRINT_IMAGEMESS:
      Serial.println("Image too messy");
      lcd.print("Image too messy");
      delay(1000);
      lcd.clear();

      return p;
    case FINGERPRINT_PACKETRECIEVEERR:
      Serial.println("Communication error");
      lcd.print("Communication error");
      delay(1000);
      lcd.clear();

      return p;
    case FINGERPRINT_FEATUREFAIL:
      Serial.println("Could not find fingerprint features");
      lcd.print("Could not find");
      lcd.setCursor(0, 1);
      lcd.print("fingerprint features");
      delay(1000);
      lcd.clear();

      return p;
    case FINGERPRINT_INVALIDIMAGE:
      Serial.println("Could not find fingerprint features");
      lcd.print("Could not find");
      lcd.setCursor(0, 1);
      lcd.print("fingerprint features");
      delay(1000);
      lcd.clear();

      return p;
    default:
      Serial.println("Unknown error");
      lcd.print("Unknown error");
      delay(1000);
      lcd.clear();

      return p;
  }

  // OK converted!
  p = finger.fingerSearch();
  if (p == FINGERPRINT_OK) {
    Serial.println("Found a print match!");
    lcd.print("Found a print match!");
    delay(1000);
    lcd.clear();
  } else if (p == FINGERPRINT_PACKETRECIEVEERR) {
    Serial.println("Communication error");
    lcd.print("Communication error");
    delay(1000);
    lcd.clear();
    return p;
  } else if (p == FINGERPRINT_NOTFOUND) {
    Serial.println("Did not find a match");
    lcd.print("Did not find a match");
    delay(1000);
    lcd.clear();
    return p;
  } else {
    Serial.println("Unknown error");
    lcd.print("Unknown error");
    delay(1000);
    lcd.clear();
    return p;
  }

  // found a match!
  Serial.print("Found ID #");
  Serial.print(finger.fingerID);
  Serial.print(" with confidence of ");
  Serial.println(finger.confidence);
  lcd.print("Found ID #");
  lcd.setCursor(11, 0);
  lcd.print(finger.fingerID);
  lcd.setCursor(15, 0);
  lcd.print(" with");
  lcd.setCursor(0, 1);
  lcd.print("confidence of ");
  lcd.setCursor(15, 1);
  lcd.print(finger.confidence);
  EspSerial.print(finger.fingerID);
  String name = EspSerial.readString();;
  delay(1000);
  lcd.clear();
  if (name != "") {
    delay(3000);
    Serial.print("Welcome ");
    Serial.println(name);
    lcd.print("Welcome");
    lcd.setCursor(8, 1);
    lcd.print(name);
    delay(5000);
    lcd.clear();
  }

  return finger.fingerID;
}