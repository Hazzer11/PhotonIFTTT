void setup() {
    Time.zone(+10);
}

int analogValue;
int tValue;
int counter=0;
int totalSun=0;
bool on=false;
bool daily=false;//has todays finished?

void loop() 
{
    analogValue = analogRead(A0);
    tValue = Time.minute();
    
    if (analogValue>700 & tValue>480 & tValue<960)
    {
        Particle.publish("sun_on_plant", PRIVATE);
        on=true;
    }
    if (tValue<480 & tValue>960)
    {
        on=false;
        daily=false;
        totalSun=0;
        counter=0;
    }
    if (on==true & daily==false)
    {
        totalSun+=analogValue;
        counter++;
    }
    if (counter>=1440&daily==false)
    {
        if (totalSun>=100800)
        {
            Particle.publish("sun_off_plant","0", PRIVATE);
        }
        else
        {
            Particle.publish("sun_off_plant",String((totalSun/700)/12), PRIVATE);
        }
        daily= true;
    }
    delay(5000); //wait 5 seconds
}
      