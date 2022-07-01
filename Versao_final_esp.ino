#include <ESP8266WiFi.h> 
#include <PCF8574.h>


// ----- DEFINIÇÃO DOS 2 PCF E RESPETIVOS ADRESSES  
PCF8574  pcf8574_1(0x20, 4, 5);
PCF8574  pcf8574_2(0x27, 4, 5);
  
int X1;                        // Variável relativa ao sensor da barragem 1
int X2;                        // Variável relativa ao sensor da barragem 2
int X3;                        // Variável relativa ao sensor da barragem 3
int X4;                        // Variável relativa ao sensor da barragem 4
int X5;                        // Variável relativa ao sensor da barragem 5
int X6;                        // Variável relativa ao sensor da barragem 6
int Y0;                        // Variável relativa à válvula da barragem 1
int Y1;                        // Variável relativa à válvula da barragem 1
int Y2;                        // Variável relativa à válvula da barragem 2
int Y3;                        // Variável relativa à válvula da barragem 3
int Y4;                        // Variável relativa à válvula da barragem 4
int Y5;                        // Variável relativa à válvula da barragem 5
int Y6;                        // Variável relativa à válvula da barragem 6
int ContadorX1=0;              // Contador de paletes da barragem 1
int Contador2X1 = 0;           // Variável auxiliar ao contador 1
int ContadorX2=0;              // Contador de paletes da barragem 2
int Contador2X2 = 0;           // Variável auxiliar ao contador 2
int ContadorX3=0;              // Contador de paletes da barragem 3
int Contador2X3 = 0;           // Variável auxiliar ao contador 3
int ContadorX4=0;              // Contador de paletes da barragem 4
int Contador2X4 = 0;           // Variável auxiliar ao contador 4
int ContadorX5=0;              // Contador de paletes da barragem 5
int Contador2X5 = 0;           // Variável auxiliar ao contador 5
int ContadorX6=0;              // Contador de paletes da barragem 6
int Contador2X6 = 0;           // Variável auxiliar ao contador 6
int Distribuicao = 1;          // Variável de iniciação da fase de distribuição
int Operacao = 0;              // Variável de iniciação da fase de operação
int posicao[6] = {1,2,3,4,5,6};// Array que guarda a posição em que está cada palete
int palete ;                   // Variável a ser recebida vinda do apache para escolha da palete a movimentar
int destino ;                  // Variável a ser recebida vinda do apache para escolha do destino a movimentar
int paletes_a_mover = 0;       // Varável que guarda o numero de barragens que cada palete tem de passar até ao destino
int calculo = 0;               // Variável auxiliar à fase de operação
int atualizar = 0;             // Variável auxiliar à fase de operação
int motor;                     // Variável que indica o estado do motor (1 - ligado; 0 - desligado)
int Contador3X1 = 0;           // Variável auxiliar ao contador 1
int Start = 0;                 // Variável auxiliar à fase de operação
int A;                         // Variável auxiliar
int aux = 1;                   // Variável auxiliar

const char* ssid = "default"; // Nome da rede Wireless 
const char* password = ""; // Password da rede Wireless
const char* host = "192.168.1.5"; // Endereço do PC do Apache

String url, url1; // Irá de conter a msg HTTP enviada para o Apache IPCONFIG
String s; // Irá conter o estado do botão nº4 (0 ou 1)

WiFiClient client; // WiFiClient, permite enviar ou receber dados por TCP/IP 
const int httpPort = 80; 



void setup() {

  pinMode(2,OUTPUT);
  pcf8574_1.pinMode(P1,INPUT);
  pcf8574_1.pinMode(P2,INPUT);
  pcf8574_1.pinMode(P3,INPUT);
  pcf8574_1.pinMode(P4,INPUT);
  pcf8574_1.pinMode(P5,INPUT);
  pcf8574_1.pinMode(P6,INPUT);
  pcf8574_2.pinMode(P0,OUTPUT);
  pcf8574_2.pinMode(P1,OUTPUT);
  pcf8574_2.pinMode(P2,OUTPUT);
  pcf8574_2.pinMode(P3,OUTPUT);
  pcf8574_2.pinMode(P4,OUTPUT);
  pcf8574_2.pinMode(P5,OUTPUT);
  pcf8574_2.pinMode(P6,OUTPUT);
  pcf8574_2.pinMode(P7,OUTPUT);

pinMode(2,OUTPUT);

  pcf8574_1.begin();
  pcf8574_2.begin();
 
Serial.begin(115200); 


// ----- ESTABLECER LIGAÇÃO WIFI COM O ESP ----
Serial.println(); Serial.println();Serial.print("Connecting to "); Serial.println(ssid); 

WiFi.mode(WIFI_STA); // O ESP irá como Client Wireless 
WiFi.begin(ssid, password); // ESP tenta ligar ao Router

// status da ligação Wifi com o router= 0 - desligado 4- ligado ...
while (WiFi.status() != WL_CONNECTED) { 
delay(500); Serial.print("."); } 

// O ESP envia por porta série, para o PC local esta informaçao: 
Serial.println("O ESP está ligado por WiFi ao Router, o Router deu-lhe o IP "); 
Serial.println(WiFi.localIP()); 
}


void loop() {

  // ---- LEITURA DOS SENSORES NA LINHA -----
  X1 = pcf8574_1.digitalRead(P1);
  X2 = pcf8574_1.digitalRead(P2);
  X3 = pcf8574_1.digitalRead(P3);
  X4 = pcf8574_1.digitalRead(P4);
  X5 = pcf8574_1.digitalRead(P5);
  X6 = pcf8574_1.digitalRead(P6);


// ----- INÍCIO DA DISTRIBUIÇÃO DAS PALETES (1 PARA CADA POSTO) ------
if (Distribuicao == 1) {
    pcf8574_2.digitalWrite(P7,0); // Motores ON 
  
    //BARRAGEM NUMERO 1
    if (X1 == 1 and Contador2X1 == 0) {
        ContadorX1 +=1;
        Contador2X1 = 1;
        delay(50);
    } else if (X1 == 0 and Contador2X1 == 1) {
    Contador2X1 = 0; 
    }
    if (ContadorX1 <= 5 and X1 == 1 and Contador3X1 == 0) {     
        pcf8574_2.digitalWrite(P1,0); 
        delay(1000);
        pcf8574_2.digitalWrite(P1,1); 
        Contador3X1 = 1; 
    }
    else if (X1 == 0) {
    pcf8574_2.digitalWrite(P1,1);
    Contador3X1 = 0;
    }
    if (ContadorX1 >= 6 and X1 == 1){
        pcf8574_2.digitalWrite(P1,0);
    }
  
    //BARRAGEM NUMERO 2
    if (X2 == 1 and Contador2X2 == 0) {
        ContadorX2 +=1;
        Contador2X2 = 1;
        delay(50);
    } else if (X2 == 0 and Contador2X2 == 1) {
        Contador2X2 = 0; 
    }
    if (ContadorX2 <= 4) {     
        pcf8574_2.digitalWrite(P2,!X2);
        delay(50);  
    }else{
        pcf8574_2.digitalWrite(P2,1);
    }

    //BARRAGEM NUMERO 3
    if (X3 == 1 and Contador2X3 == 0) {
        ContadorX3 +=1;
        Contador2X3 = 1;
        delay(50);
    } else if (X3 == 0 and Contador2X3 == 1) {
        Contador2X3 = 0; 
    }
    if (ContadorX3 <= 3) {     
        pcf8574_2.digitalWrite(P3,!X3);
        delay(50);  
    }else{
        pcf8574_2.digitalWrite(P3,1);
    }

    //BARRAGEM NUMERO 4  
    if (X4 == 1 and Contador2X4 == 0) {
        ContadorX4 +=1;
        Contador2X4 = 1;
        delay(50);
    } else if (X4 == 0 and Contador2X4 == 1) {
        Contador2X4 = 0; 
    }
    if (ContadorX4 <= 2) {     
        pcf8574_2.digitalWrite(P4,!X4);
        delay(50);  
    }else{
        pcf8574_2.digitalWrite(P4,1);
    }
  
    //BARRAGEM NUMERO 5  
    if (X5 == 1 and Contador2X5 == 0) {
        ContadorX5 +=1;
        Contador2X5 = 1;
        delay(50);
    } else if (X5 == 0 and Contador2X5 == 1) {
        Contador2X5 = 0; 
    }
    if (ContadorX5 <= 1) {     
        pcf8574_2.digitalWrite(P5,!X5);
        delay(50);  
    }else{
        pcf8574_2.digitalWrite(P5,1);
    }

    //BARRAGEM NUMERO 6
    pcf8574_2.digitalWrite(P6,1);

    // ------ RESET DOS CONTADORES APÓS FIM DA DISTRIBUIÇÃO ------
    if ( X1 == 1 and X2 == 1 and X3 == 1 and X4 == 1 and X5 == 1 and X6 == 1) {
        pcf8574_2.digitalWrite(P7,1); // Motores OFF 
        Distribuicao = 0;
        ContadorX1 = 0;
        ContadorX2 = 0;
        ContadorX3 = 0;
        ContadorX4 = 0;
        ContadorX5 = 0;
        ContadorX6 = 0;
        Contador2X1 = 0;
        Contador2X2 = 0;
        Contador2X3 = 0;
        Contador2X4 = 0;
        Contador2X5 = 0;
        Contador2X6 = 0;
        Contador3X1 = 0;
        Operacao = 1;
        calculo = 1;
        
    }  
}

// --------- FASE DE DISTRIBUIÇÃO DE PALETES PARA OS POSTOS DESEJADOS ------
if (Operacao == 1) {

    if (Start == 0) {
      pcf8574_2.digitalWrite(P7,1); // Motores OFF
    }

    //   ----- Calculo do numero de posições a avançar por cada palete ----
    if ( calculo == 1 and destino > 0 and palete > 0) {  

        if (destino >= posicao[palete - 1]) {
            paletes_a_mover = destino - posicao[palete - 1];
        }

        if (posicao[palete - 1] > destino) {
            paletes_a_mover = destino - posicao[palete - 1] + 6;
        }
        if (paletes_a_mover > 0) {
          calculo = 0;
          atualizar = 1;
        }
    }

    //   ----- Atualização da posição de cada palete ----
    if (atualizar == 1) {

        for (int x; x < 6; x = x+1) {
            posicao[x] = posicao[x] + paletes_a_mover;
            if (posicao[x] > 6) {
                posicao[x] = posicao[x] - 6;
            }
            if (x == 5) {
                atualizar = 0;
            }
        }
    }

    // ---- ORDEM DE INICIO DE MOVIMENTAÇÃO DAS PALETES DEPOIS DE REUNIDAS AS CONDIÇOES NECESSARIAS ----
    if (atualizar == 0 and paletes_a_mover > 0 and Start == 0) {
        ContadorX1 = 0;
        ContadorX2 = 0;
        ContadorX3 = 0;
        ContadorX4 = 0;
        ContadorX5 = 0;
        ContadorX6 = 0;
        Contador2X1 = 0;
        Contador2X2 = 0;
        Contador2X3 = 0;
        Contador2X4 = 0;
        Contador2X5 = 0;
        Contador2X6 = 0;
        Contador3X1 = 0;
        Start = 1;
    }

    //   --- Movimentação das paletes para os seus destinos ----
    if (Start == 1) {
        pcf8574_2.digitalWrite(P7,0); // Motores ON 
  
        //BARRAGEM NUMERO 1   
        if (X1 == 1 and Contador2X1 == 0) {
          ContadorX1 +=1;
          Contador2X1 = 1;
          delay(50);
        } else if (X1 == 0 and Contador2X1 == 1) {
          Contador2X1 = 0; 
        }
        if (ContadorX1 <= paletes_a_mover and X1 == 1 and Contador3X1 == 0) {     
          pcf8574_2.digitalWrite(P1,0); 
          delay(1000);
          pcf8574_2.digitalWrite(P1,1); 
          Contador3X1 = 1; 
        }
        else if (X1 == 0) {
          pcf8574_2.digitalWrite(P1,1);
          Contador3X1 = 0;
        }
        if (ContadorX1 > paletes_a_mover and X1 == 1){
          pcf8574_2.digitalWrite(P1,0);
        }
  
        //BARRAGEM NUMERO 2
        if (X2 == 1 and Contador2X2 == 0) {
            ContadorX2 +=1;
            Contador2X2 = 1;
            delay(50);
        } else if (X2 == 0 and Contador2X2 == 1) {
            Contador2X2 = 0; 
        }
        if (ContadorX2 <= paletes_a_mover) {     
            pcf8574_2.digitalWrite(P2,!X2);
            delay(50);  
        }else{
            pcf8574_2.digitalWrite(P2,1);
        }

        //BARRAGEM NUMERO 3
        if (X3 == 1 and Contador2X3 == 0) {
            ContadorX3 +=1;
            Contador2X3 = 1;
            delay(50);
        } else if (X3 == 0 and Contador2X3 == 1) {
            Contador2X3 = 0; 
        }
        if (ContadorX3 <= paletes_a_mover) {     
            pcf8574_2.digitalWrite(P3,!X3);
            delay(50);  
        }else{
            pcf8574_2.digitalWrite(P3,1);
        }

        //BARRAGEM NUMERO 4
        if (X4 == 1 and Contador2X4 == 0) {
            ContadorX4 +=1;
            Contador2X4 = 1;
            delay(50);
        } else if (X4 == 0 and Contador2X4 == 1) {
            Contador2X4 = 0; 
        }
        if (ContadorX4 <= paletes_a_mover) {     
            pcf8574_2.digitalWrite(P4,!X4);
            delay(50);  
        }else{
            pcf8574_2.digitalWrite(P4,1);
        }
  
        //BARRAGEM NUMERO 5
        if (X5 == 1 and Contador2X5 == 0) {
            ContadorX5 +=1;
            Contador2X5 = 1;
            delay(50);
        } else if (X5 == 0 and Contador2X5 == 1) {
            Contador2X5 = 0; 
        }
        if (ContadorX5 <= paletes_a_mover) {     
            pcf8574_2.digitalWrite(P5,!X5);
            delay(50);  
        }else{
            pcf8574_2.digitalWrite(P5,1);
        }

        //BARRAGEM NUMERO 6
        if (X6 == 1 and Contador2X6 == 0) {
            ContadorX6 +=1;
            Contador2X6 = 1;
            delay(50);
        } else if (X6 == 0 and Contador2X6 == 1) {
            Contador2X6 = 0; 
        }
        if (ContadorX6 <= paletes_a_mover) {     
            pcf8574_2.digitalWrite(P6,!X6);
            delay(50);  
        }else{
            pcf8574_2.digitalWrite(P6,1);
        }

        
        // ---------- RESET DAS VARIÁVEIS QUANDO A MOVIMENTAÇÃO CHEGA AO FIM -----------
        if ( X1 == 1 and X2 == 1 and X3 == 1 and X4 == 1 and X5 == 1 and X6 == 1 and ContadorX1 == paletes_a_mover+1) {
            calculo = 1;
            atualizar = 1 ;
            ContadorX1 = 0;
            ContadorX2 = 0;
            ContadorX3 = 0;
            ContadorX4 = 0;
            ContadorX5 = 0;
            ContadorX6 = 0;
            Contador2X1 = 0;
            Contador2X2 = 0;
            Contador2X3 = 0;
            Contador2X4 = 0;
            Contador2X5 = 0;
            Contador2X6 = 0;
            Contador3X1 = 0;
            Start = 0;
        } 
    }

}


// ------------------- TENTA LIGAR POR TCP/IP ao APACHE
// Se o status da ligação TCP/IP entre o ESP e o PC remoto for 0 (client.status= 0 - desligado) 

// Neste caso, o ESP tenta estabelecer ligacao TCP/IP com o Apache 
  if(client.status()==0){ 
    Serial.print("connecting to "); Serial.println(host); // envia para o serial monitor 

    if (!client.connect(host, httpPort)) { // ------------------- Tenta LIGAÇAO TCP
      Serial.println("connection failed"); 
      client.flush(); 
      delay(100); 
    } //IF 
  } // IF
 

// ----------------- SE LIGACAO TCP ESTABELECIDA -------------
// Se o status da ligação for 4, significa que a ligação TCP/IP está estabelecida entre o ESP e o Apache 
  if(client.status()==4){

    Y0=pcf8574_2.digitalRead(P1); 
    Y1=pcf8574_2.digitalRead(P2);
    Y2=pcf8574_2.digitalRead(P3);
    Y3=pcf8574_2.digitalRead(P4);
    Y4=pcf8574_2.digitalRead(P5);
    Y6=pcf8574_2.digitalRead(P6);
    motor=pcf8574_2.digitalRead(P7);

    // --------- CRIAÇÃO DA URL A MANDAR PARA O SERVIDOR ---------
    url = "GET /Update2.php?saidaY0=000&saidaY1=111&saidaY2=222&saidaY3=333&saidaY4=444&saidaY5=555&saidaY6=666&motor=234&saidaX1=101&saidaX2=202&saidaX3=303&saidaX4=404&saidaX5=505&saidaX6=606&palete1=011&palete2=012&palete3=013&palete4=014&palete5=015&palete6=016&start=999&distribuicao=888&operacao=777";
    url.replace("000",String(Y0));
    url.replace("111",String(Y1));
    url.replace("222",String(Y2));
    url.replace("333",String(Y3));
    url.replace("444",String(Y4));
    url.replace("555",String(Y5));
    url.replace("666",String(Y6));
    url.replace("234",String(motor));
    url.replace("101",String(X1));
    url.replace("202",String(X2));
    url.replace("303",String(X3));
    url.replace("404",String(X4));
    url.replace("505",String(X5));
    url.replace("606",String(X6));
    url.replace("011",String(posicao[0]));
    url.replace("012",String(posicao[1]));
    url.replace("013",String(posicao[2]));
    url.replace("014",String(posicao[3]));
    url.replace("015",String(posicao[4]));
    url.replace("016",String(posicao[5]));
    url.replace("999",String(Start));
    url.replace("888",String(Distribuicao));
    url.replace("777",String(calculo));
   
    client.println(url);
    client.println(" HTTP/1.1");        
    client.println("Host: 192.168.1.5"); 
    client.println("Connection: close");
    Serial.println(url);
    
 
    delay(100); 

  } 


// ------------------- SE CHEGARAM DADOS por TCP/IP -------
  if (client.available() > 0) { // Se o ESP tiver recebido bytes 
    
    // Le todos os carateres enviados pelo Apache até receber o caracter 'ç' ou exceder um tempo máximo. 
    String line = client.readStringUntil('ç'); 

    // -------TRANSFORMAÇÃO DOS VALORES RECEBIDOS PARA ASCII-------
    palete = line[23]- 48;    
    destino = line[25]-48;
  
    client.flush(); 

  }

// ------ ALTERAÇÃO DA LUZ DO ESP PARA VISUALMENTE PERCEBER A MUDANÇA DE CICLO ------
if (A==1){
  digitalWrite(2,1);
  A = 0;
} else {
  digitalWrite(2,0);
  A = 1;
}

Serial.println(paletes_a_mover);
Serial.print(posicao[0]); Serial.print(posicao[1]); Serial.print(posicao[2]); Serial.print(posicao[3]); Serial.print(posicao[4]); Serial.println(posicao[5]);
Serial.println(calculo);
  Serial.print(ContadorX1);Serial.print(ContadorX2);Serial.print(ContadorX3);Serial.print(ContadorX4);Serial.print(ContadorX5);Serial.print(ContadorX6);
  Serial.println(" ");
} // Fim do Loop
