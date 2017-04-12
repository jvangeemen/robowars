/*
 * Interrupt pins:
Arduino                         Arduino
Pin     External                Pin     Pin Change
        Interrupt                       Interrupt
               Port                               Port
 3      INT0   PD0              8       PCINT4    PB4
 2      INT1   PD1              9       PCINT5    PB5
 0      INT2   PD2              10      PCINT6    PB6
 1      INT3   PD3              11      PCINT7    PB7
 7      INT6   PE6              SCK/15  PCINT1    PB1
                                MOSI/16 PCINT2    PB2
                                MISO/14 PCINT3    PB3

                                on ICSP:
                                SCK/15:  PCINT1 (PB1)
                                MOSI/16: PCINT2 (PB2)
                                MISO/14: PCINT3 (PB3)
 */
