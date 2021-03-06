/* -------------------------Definicao dos Pinos---------------------------- */
#define RearRightForwardPin 9
#define RearRightBackwardPin 8
#define RearLeftForwardPin 5
#define RearLeftBackwardPin 4
#define FrontRightForwardPin 7
#define FrontRightBackwardPin 6
#define FrontLeftForwardPin 3
#define FrontLeftBackwardPin 2
#define RearRightPotenciaPin 12
#define RearLeftPotenciaPin 11
#define FrontRightPotenciaPin 13
#define FrontLeftPotenciaPin 10
/* ------------------------------------------------------------------------ */

/* ---------------Variaveis que serao enviadas aos pinos------------------- */
int RearRightForward;
int RearRightBackward;
int RearLeftForward;
int RearLeftBackward;
int FrontRightForward;
int FrontRightBackward;
int FrontLeftForward;
int FrontLeftBackward;
int RearRightPotencia;
int RearLeftPotencia;
int FrontRightPotencia;
int FrontLeftPotencia;
/* ------------------------------------------------------------------------ */

String str;
String serialData;

/* ------------------------------------------------------------------------ */
void setup()
{  
	// Inicializacao das portas seriais (0 - utilizada para debug, 1 - Troca de dados do bluetooth)
	Serial.begin(115200); 
	Serial1.begin(9600);  

	// Seta o modo de opera??o dos pinos
	pinMode(RearRightForwardPin, OUTPUT);
	pinMode(RearRightBackwardPin, OUTPUT);
	pinMode(RearLeftForwardPin, OUTPUT);
	pinMode(RearLeftBackwardPin, OUTPUT);
	pinMode(FrontRightForwardPin, OUTPUT);
	pinMode(FrontRightBackwardPin, OUTPUT);
	pinMode(FrontLeftForwardPin, OUTPUT);
	pinMode(FrontLeftBackwardPin, OUTPUT);
	pinMode(RearRightPotenciaPin, OUTPUT);
	pinMode(RearLeftPotenciaPin, OUTPUT);
	pinMode(FrontRightPotenciaPin, OUTPUT);
	pinMode(FrontLeftPotenciaPin, OUTPUT);
		
        // Para os motores ao primeiro momento
	PararMotores();
    
}

void serialEvent1(){
  serialData = String("");
  while(Serial1.available())
  {
    serialData = serialData + char(Serial1.read());
    delay(1);
  }
  
  ImprimirVariavelFormatada("serialData: ", serialData); 
}

void loop()
{
  if(serialData.endsWith(";"))
  {
    str = String(serialData);
    ImprimirVariavelFormatada("str: ", str); 
    boolean resultado = LerMensagem(); 
    str = "";
    serialData = "";
  }
}

boolean LerMensagem()
{  
  // mensagem do tipo Motor
  if(str.startsWith("M"))
  {
      String motor = str.substring(1,3);
      String sentidoStr = str.substring(3,4);
      boolean sentido = sentidoStr == "-" ? LOW : HIGH;	 
      int potencia = str.substring(4).toInt();	 

       /*ImprimirVariavelFormatada("Motor: ", motor);
       ImprimirVariavelFormatada("sentidoStr: ",sentidoStr);
       ImprimirVariavelFormatada("sentido: ",sentido);
       ImprimirVariavelFormatada("sentidoI: ",!sentido);
       ImprimirVariavelFormatada("potencia: ",potencia);*/                
	 
      // frontal esquerdo
      if(motor == "FE")
      {        
        digitalWrite( FrontLeftForwardPin, sentido );
        digitalWrite( FrontLeftBackwardPin, !sentido );
        analogWrite(  FrontLeftPotenciaPin, potencia );
        return true;
      }	
     
     // frontal direito
      if(motor == "FD")
      {        
        digitalWrite( FrontRightForwardPin, sentido );
        digitalWrite( FrontRightBackwardPin, !sentido );
        analogWrite(  FrontRightPotenciaPin, potencia );
        return true;
      }
     
      //traseiro esquerdo
      if(motor == "TE")
      {       
        digitalWrite( RearLeftForwardPin, sentido );
        digitalWrite( RearLeftBackwardPin, !sentido );
        analogWrite(  RearLeftPotenciaPin, potencia );
        return true;
      }
     
      //traseiro direito
      if(motor == "TD")
      {        
        digitalWrite( RearRightForwardPin, sentido );
        digitalWrite( RearRightBackwardPin, !sentido );
        analogWrite(  RearRightPotenciaPin, potencia );
        return true;
      }	
      
      ImprimirVariavelFormatada("Invalido", "");      
      return false;
  }
  
  ImprimirVariavelFormatada("Nao e motor", "");
  return false;
}

int getInt(String text, int size)
{
  char temp[size+1];
  text.toCharArray(temp, size+1);
  int x = atoi(temp);
  return x;
} 

// Para os motores setando as direcoes para low e o pwm para 0
void PararMotores()
{
	digitalWrite( RearRightForwardPin, LOW );
	digitalWrite( RearRightBackwardPin, LOW );
	digitalWrite( RearLeftForwardPin, LOW );
	digitalWrite( RearLeftBackwardPin, LOW );
	digitalWrite( FrontRightForwardPin, LOW );
	digitalWrite( FrontRightBackwardPin, LOW );
	digitalWrite( FrontLeftForwardPin, LOW );
	digitalWrite( FrontLeftBackwardPin, LOW );
	analogWrite( RearRightPotenciaPin, 0 );
	analogWrite( RearLeftPotenciaPin, 0 );
	analogWrite( FrontRightPotenciaPin, 0 );
	analogWrite( FrontLeftPotenciaPin, 0 );
}

void  ImprimirVariavelFormatada (String titulo, String texto)
{
    Serial.print(titulo);
    Serial.println(texto);
}

void  ImprimirVariavelFormatada  (String titulo, int valor)
{
    Serial.print(titulo);
    Serial.println(valor);
}

void  ImprimirVariavelFormatada  (String titulo, boolean valor)
{
    Serial.print(titulo);
    Serial.println(valor);
}

//void  ImprimirVariavelFormatada  (String titulo, byte valor)
//{
//    Serial.print(titulo);
//    Serial.println(valor);
//}

