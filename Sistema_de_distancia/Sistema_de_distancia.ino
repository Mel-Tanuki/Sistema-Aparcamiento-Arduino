// Pines utilizados para alertar dependiendo la distancia.
#define LEDVERDE 2
#define LEDAMARILLO 3
#define LEDROJO 4
#define TRIGGER 5
#define ECHO 6
#define BUZZER 9
 
// Constantes
const float sonido = 34300.0; // Velocidad del sonido en cm/s
const float umbral1 = 30.0;
const float umbral2 = 20.0;
const float umbral3 = 10.0;
 
void setup() {
  // Aquí se inicia el monitor serie
  Serial.begin(9600);
 
  // Modo input/output de los pines
  pinMode(LEDVERDE, OUTPUT);
  pinMode(LEDAMARILLO, OUTPUT);
  pinMode(LEDROJO, OUTPUT);
  pinMode(ECHO, INPUT);
  pinMode(TRIGGER, OUTPUT);
  pinMode(BUZZER, OUTPUT);
 
  // Esto es para apagar todos los LEDs
  apagarLEDs();
 
}
 
void loop() {
  // Se prepara el sensor ultrasonico
  iniciarTrigger();
 
  // Esto es para obtener la distancia
  float distancia = calcularDistancia();
 
  // Se apagan LED
  apagarLEDs();
 
  // Con esto aparece la alerta que indica que se está dentro del rango mucha cercania.
  if (distancia < umbral1)
  {
    // !Alerta!
    alertas(distancia);
  }
 
}
 
// Se apagan los LED
void apagarLEDs()
{
  // LOW LED
  digitalWrite(LEDVERDE, LOW);
  digitalWrite(LEDAMARILLO, LOW);
  digitalWrite(LEDROJO, LOW);
}
 
// Permite comprobar para lanzar una alerta sonora
void alertas(float distancia)
{
  if (distancia < umbral1 && distancia >= umbral2)
  {
    // HIGH LED verde
    digitalWrite(LEDVERDE, HIGH);
    tone(BUZZER, 2000, 200);
  }
  else if (distancia < umbral2 && distancia > umbral3)
  {
    // HIGH LED naranja o amarillo (hasta ahora en la placa fisica he utilizado naranja, pues no cuento con amarillo)
    digitalWrite(LEDAMARILLO, HIGH);
    tone(BUZZER, 2500, 200);
  }
  else if (distancia <= umbral3)
  {
    // HIGH LED rojo
    digitalWrite(LEDROJO, HIGH);
    tone(BUZZER, 3000, 200);
  }
}
 
// Método que calcula la distancia a la que se encuentra un objeto.
// Devuelve una variable tipo float que contiene la distancia
float calcularDistancia()
{
  // La función pulseIn obtiene el tiempo que tarda en cambiar entre estados, en este caso a HIGH
  unsigned long tiempo = pulseIn(ECHO, HIGH);
 
  // Obtenemos la distancia en cm, hay que convertir el tiempo en segudos ya que está en microsegundos
  // por eso se multiplica por 0.000001
  float distancia = tiempo * 0.000001 * sonido / 2.0;
  Serial.print(distancia);
  Serial.print("cm");
  Serial.println();
  delay(500);
 
  return distancia;
}
 
// Método que inicia la secuencia del Trigger para comenzar a medir
void iniciarTrigger()
{
  // Trigger en LOW y esperar 2 ms
  digitalWrite(TRIGGER, LOW);
  delayMicroseconds(2);
 
  // pin Trigger a estado HIGH y esperar 10 ms
  digitalWrite(TRIGGER, HIGH);
  delayMicroseconds(10);
 
  // pin Trigger en LOW
  digitalWrite(TRIGGER, LOW);
}
