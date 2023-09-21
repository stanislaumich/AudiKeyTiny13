#include <avr/io.h>
#include <avr/wdt.h> // здесь организована работа с ватчдогом
#include <avr/sleep.h> // здесь описаны режимы сна
#include <avr/interrupt.h> // работа с прерываниями

// http://www.count-zero.ru/2016/attiny13/

volatile uint8_t i;
ISR (WDT_vect) {
 if ((++i%64) == 0)
         PORTB |= (1<<PB3); // включаем светодиод
 else
         PORTB &= ~(1<<PB3); // выключаем светодиод

         WDTCR |= (1<<WDTIE); // разрешаем прерывания по ватчдогу. Иначе будет резет.
}

int main() {

        DDRB = (1<<PB3); // на этом пине висит светодиод
        i=0;

        //инициализация ватчдога
        wdt_reset(); // сбрасываем
        wdt_enable(WDTO_60MS); // разрешаем ватчдог 1 сек
        WDTCR |= (1<<WDTIE); // разрешаем прерывания по ватчдогу. Иначе будет резет.
        sei(); // разрешаем прерывания

        set_sleep_mode(SLEEP_MODE_PWR_DOWN); // если спать - то на полную
        while(1) {
                sleep_enable(); // разрешаем сон
                sleep_cpu(); // спать!
        }
}
https://4pda.to/forum/index.php?showtopic=953401&st=420
https://soltau.ru/index.php/arduino/item/394-kak-sdelat-kopiyu-klyucha-dlya-domofona-v-domashnikh-usloviyakh
#include <OneWire.h>
OneWire iButton(10); // создаём объект 1-wire на 10 выводе

void setup (void) {
  Serial.begin(9600);
}

void loop(void) {
  delay(1000); // задержка 1 сек
  byte addr[8]; // массив для хранения данных ключа
  
  if ( !iButton.search(addr) ) { // если ключ не приложен
      Serial.println("No key connected..."); // сообщаем об этом
      return; // и прерываем программу
  }
  
  Serial.print("Key : ");
  for(int i=0; i<8; i++) {
    Serial.print(addr[i], HEX); // выводим побайтно данные ключа
    Serial.print(" ");
  }
  Serial.println();
  iButton.reset(); // сброс ключа
}
