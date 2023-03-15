int led0 = 2;
int led1 = 3;
int led2 = 10;
int speaker = 4;
int button0 = 7;
int button1 = 8;
int button2 = 5;
bool button_state0 = LOW;
bool button_state1 = LOW;
bool button_state2 = LOW;
bool player_lost = LOW;
int round_num = 1;
const int len_sequence = 5;
int rand_sequence[len_sequence];


void setup() {
  pinMode(led0, OUTPUT);
  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);
  pinMode(speaker, OUTPUT);
  pinMode(button0, INPUT);
  pinMode(button1, INPUT);
  pinMode(button2, INPUT);
  Serial.begin(9600);
  randomSeed(analogRead(A1));
}


void loop() {
  while (player_lost == LOW) {
    if (round_num == 1) {
    // generate a random sequence of 10 1's and 0's and store it in the array:
      for (int i = 0; i < len_sequence; i++) {
        rand_sequence[i] = random(3);
  }
    }
  // Step 1: Sending random signal of 0's and 1's to the LED's and speaker:

  // Making LEDs flash to a random sequence: led0 = 0, led1 = 1
  // print the random sequence on Serial Monitor
    for (int i = 0; i < round_num; i++) {
      Serial.print(rand_sequence[i]);
    }
    Serial.println();
    for (int i = 0; i < round_num; i++) {
      int bit = rand_sequence[i];
      if (bit == 0) {
          digitalWrite(led0, HIGH);   
          tone(speaker, 440);      
          delay(250);
          noTone(speaker);                     
          digitalWrite(led0, LOW);          
          delay(250);                      
      }
      else if (bit == 1) {
        digitalWrite(led1, HIGH);
        tone(speaker, 523);
        delay(250);
        noTone(speaker);
        digitalWrite(led1, LOW);
        delay(250);
      }
      else if (bit == 2) {
        digitalWrite(led2, HIGH);
        tone(speaker, 698);
        delay(250);
        noTone(speaker),
        digitalWrite(led2, LOW);
        delay(250);
      }
    }

    // delay(500);
    // Start light and noise
    // digitalWrite(led0, HIGH);
    // digitalWrite(led1, HIGH);
    // tone(speaker, 1000);
    // delay(750);
    // noTone(speaker);
    // digitalWrite(led0, LOW);
    // digitalWrite(led1, LOW);
    // delay(250);

    // Step 2: Buttons
    for (int i = 0; i < round_num; i ++) {
      button_state0 = LOW;
      button_state1 = LOW;
      button_state2 = LOW;
      int button_start_time = millis();
      // Wait for player to push a button
      while (button_state0 == LOW and button_state1 == LOW and button_state2 == LOW and player_lost == LOW) {
        button_state0 = digitalRead(button0);
        button_state1 = digitalRead(button1);
        button_state2 = digitalRead(button2);
        int current_time = millis();
        if (current_time - button_start_time > 4000) {
          Serial.println("You waited too long!");
          round_num = 1;
          digitalWrite(led0, HIGH);
          digitalWrite(led1, HIGH);
          digitalWrite(led2, HIGH);
          tone(speaker, 207);
          delay(750);
          noTone(speaker);
          digitalWrite(led0, LOW);
          digitalWrite(led1, LOW);
          digitalWrite(led2, LOW);
          delay(250); 
          player_lost = HIGH;
        } 
      }

      if (button_state0 == HIGH and player_lost == LOW) {
          if (rand_sequence[i] == 0) {
            digitalWrite(led0, HIGH);   
            tone(speaker, 440);      
            delay(250);
            noTone(speaker);                     
            digitalWrite(led0, LOW);          
            // delay(150); 
          }
          else {
            Serial.println("You incorrectly pressed 0!");
            round_num = 1;
            digitalWrite(led0, HIGH);
            digitalWrite(led1, HIGH);
            digitalWrite(led2, HIGH);
            tone(speaker, 207);
            delay(750);
            noTone(speaker);
            digitalWrite(led0, LOW);
            digitalWrite(led1, LOW);
            digitalWrite(led2, LOW);
            delay(250);
            player_lost = HIGH; 
          }
      }

      else if (button_state1 == HIGH and player_lost == LOW) {
          if (rand_sequence[i] == 1) {
            digitalWrite(led1, HIGH);   
            tone(speaker, 523);      
            delay(250);
            noTone(speaker);                     
            digitalWrite(led1, LOW);          
            // delay(150); 
          }
          else {
            Serial.println("You incorrectly pressed 1!");
            round_num = 1;
            digitalWrite(led0, HIGH);
            digitalWrite(led1, HIGH);
            digitalWrite(led2, HIGH);
            tone(speaker, 207);
            delay(750);
            noTone(speaker);
            digitalWrite(led0, LOW);
            digitalWrite(led1, LOW);
            digitalWrite(led2, LOW);
            delay(250);
            player_lost = HIGH; 
          }
      }

      else if (button_state2 == HIGH and player_lost == LOW) {
        if (rand_sequence[i] == 2) {
          digitalWrite(led2, HIGH);
          tone(speaker, 698);
          delay(250);
          noTone(speaker);
          digitalWrite(led2, LOW);
        }
        else {
            Serial.println("You incorrectly pressed 2!");
            round_num = 1;
            digitalWrite(led0, HIGH);
            digitalWrite(led1, HIGH);
            digitalWrite(led2, HIGH);
            tone(speaker, 207);
            delay(750);
            noTone(speaker);
            digitalWrite(led0, LOW);
            digitalWrite(led1, LOW);
            digitalWrite(led2, LOW);
            delay(250);
            player_lost = HIGH; 
        }
      }

      while (button_state0 == HIGH or button_state1 == HIGH and player_lost == LOW) {
        // Wait for player to release button
        button_state0 = digitalRead(button0);
        button_state1 = digitalRead(button1);
      }
      

    }              

    if (player_lost == LOW and round_num < len_sequence) {
      delay(250);
      Serial.println("Correct!");
      int b = 988;
      int e = 1318;
      tone(speaker, b);
      delay(75);
      tone(speaker, e);
      delay(350);
      noTone(speaker);
      round_num ++;
      delay(250);
    }
    else if (player_lost == LOW and round_num == len_sequence) {
      Serial.println("You win!");
      round_num = 1;
      int low_g = 391;
      int low_c = 523;
      int low_e = 659;
      int high_g = 784;
      int high_c = 1046;
      int high_e = 1318;
      int high_high_g = 1568;
      int low_a_b = 415;
      int low_e_b = 622;
      int high_a_b = 830;
      int high_e_b = 1244;
      int high_high_a_b = 1661;
      int low_b_b = 466;
      int low_d = 587;
      int low_f = 698;
      int high_b_b = 932;
      int high_d = 1175;
      int high_f = 1397;
      int high_high_b_b = 1864;
      int high_high_c = 2093;

      // First triplet run:
      tone(speaker, low_g);
      delay(134);
      tone(speaker, low_c);
      delay(133);
      tone(speaker, low_e);
      delay(133);
      tone(speaker, high_g);
      delay(134);
      tone(speaker, high_c);
      delay(133);
      tone(speaker, high_e);
      delay(133);
      tone(speaker, high_high_g);
      delay(400);
      tone(speaker, high_e);
      delay(400);

      // Second triplet run:
      tone(speaker, low_a_b);
      delay(134);
      tone(speaker, low_c);
      delay(133);
      tone(speaker, low_e_b);
      delay(133);
      tone(speaker, high_a_b);
      delay(134);
      tone(speaker, high_c);
      delay(133);
      tone(speaker, high_e_b);
      delay(133);
      tone(speaker, high_high_a_b);
      delay(400);
      tone(speaker, high_e_b);
      delay(400);

      // Third triplet run and ending:
      tone(speaker, low_b_b);
      delay(134);
      tone(speaker, low_d);
      delay(133);
      tone(speaker, low_f);
      delay(133);
      tone(speaker, high_b_b);
      delay(134);
      tone(speaker, high_d);
      delay(133);
      tone(speaker, high_f);
      delay(133);
      tone(speaker, high_high_b_b);
      delay(400);
      tone(speaker, high_high_b_b);
      delay(134);
      tone(speaker, high_high_b_b);
      delay(133);
      tone(speaker, high_high_b_b);
      delay(133);
      tone(speaker, high_high_c);
      delay(800);
      noTone(speaker);
    }
    delay(1000);

    }
    
  player_lost = LOW;

}
