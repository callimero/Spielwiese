/*
   Demofunktionen als Anregung
*/


// Hilfsvariablen im globalen Kontext
// Arrays fürs Merken von Koordinaten/Geschwindigkeit/etc
int xc[40];
int yc[40];
int sx[40];
int sy[40];
int n[40];
int g[40];

int idx;
char buf[12]; // itoa() buffer
elapsedMillis wait;    // Auto updating variable, fürs Timing


// Supportfunktion für die Zufallszahlen
void new_num(int c)
{
  g[c]  = rand() % 25 + 4;
  xc[c] = rand() % 3800;
  yc[c] = rand() % 3800;
  n[c]  = rand() % 100;
  wait = 0;
}

// Zufallszahlen
void zahlensalat()
{
  //Zeichnen
  for (int i = 0; i <= 30; i++) // 30 Zahlen
  {
    if (g[i] != 0)
    {
      draw_string(itoa(n[i], buf, 10), xc[i], yc[i], g[i]);
    }
    else
    {
      new_num(i); // Init wenn noch nicht belegt, auskommentieren wenn langsames füllen erwünscht
    }

  }
  if (wait > 500) new_num(rand() % 30); // Alle 500ms einmal neue Zahl
}


// Ziffern skalieren bis zur Löschung.
void zahlensalat2()
{
  //Zeichnen
  for (int i = 0; i <= 30; i++) // 30 Zahlen
  {
    if (g[i] > 0)
    {
      draw_string(itoa(n[i], buf, 10), xc[i], yc[i], g[i] / 100);
      g[i] = g[i] - 5;
    }
    else
    {
      new_num(i);
      g[i] = g[i] * 100;
    }
  }
}


// Zufallszahlen (sehr wuselig, in jedem Frame unterschdlich)
void rnd_numbers()
{
  // Zufallszahlen (Zehn Stück)
  char buf[12];
  for (int i = 0; i <= 10; i++)
  {
    draw_string(itoa(rand() % 100, buf, 10), rand() % 3800, rand() % 3800, rand() % 25 + 4);
  }
}




// Hallo World der Vektordisplays
void HalloMake()
{
  // Koordinatenbereich X/Y 0..4095
  // die meissten Oszilloskope haben aber einen 4:3 Bildschirm! -> Verzerrungen die herausgerechnet werden müssen
  // X Zeichnen mit einfachen Befehlen: Ursprung ist unten Links
  moveto(3000, 3000);
  lineto(3500, 3500);
  moveto(3000, 3500);
  lineto(3500, 3000);

  // Einfache Supportfunktion um Rechtecke zu zeichnen aus Simple.ino
  draw_rect(0, 0, 4095, 4095);

  // Text/String "Text", X,Y, Groesse
  draw_string("Hallo Make-Magazin!", 100, 150, 6);

  // in objects.c definierte Objekte Zeichnen.
  // Parameter: Objektnummer, X,Y, Größe, Rotation (0== aufrecht/Blender +Y, linksrum :-))
  draw_object(11, 2000, 2000, 40, 0); // Das ist Makey...
}


// Drehender Makey
int wm = 0;  //globaler Merker der Rotation
void SpinMakey()
{
  wm = (wm + 1) % 360;
  draw_object(11, 2000, 2000, 40, wm); // Das ist Makey... Wirds ihm schlecht?
}


// Zufallslinien (in jedem Frame unterschiedlich)
void rnd_lines()
{
  // Zufallslinen (Zehn Stück)
  for (int i = 0; i <= 10; i++)
  {
    moveto(rand() % 4096, rand() % 4096);
    lineto(rand() % 4096, rand() % 4096);
  }
}




// Zufallslinien als offener Linienzug (in jedem Frame unterschiedlich)
void rnd_poly()
{
  // Polygon
  moveto(rand() % 4096, rand() % 4096); //Startpunkt
  for (int i = 0; i <= 10; i++) // Zehn Punkte
  {
    lineto(rand() % 4096, rand() % 4096);
  }
}


// Linien in Sternenform
void rnd_star()
{
  // "Stern"
  for (int i = 0; i <= 40; i++) // 40 Linien
  {
    moveto(rand() % 4096, rand() % 4096); //Startpunkt
    lineto(2048, 2048);
  }
}


// Linien in Sternenform 2, hier aber bleiben die Linien etwas länger stehen
void rnd_star2()
{
  // "Stern"
  xc[idx] = rand() % 4096;
  yc[idx] = rand() % 4096;
  idx = (idx + 1) % 40;
  for (int i = 0; i < 40; i++) // 40 Linien
  {
    moveto(xc[i], yc[i]); //Startpunkt
    lineto(2048, 2048);
  }
}


// Weltkarte mit Hoystick bewegbar/skalierbar
int wx, wy;
int zoom = 20;
void world()
{
  if (!digitalRead(BUTT) == HIGH )
  {
    joystick();
    wx = wx - joyx / 4;
    wy = wy - joyy / 4;
    zoom = 2 + joyz / 4;
  }
  draw_object(7, 2000 + wx, 2000 + wy, zoom, 0);  // meine Karte ist auf 4 Objekte verteilt
  draw_object(8, 2000 + wx, 2000 + wy, zoom, 0);
  draw_object(9, 2000 + wx, 2000 + wy, zoom, 0);
  draw_object(10, 2000 + wx, 2000 + wy, zoom, 0);
  //draw_string("Joy Button halten und Joystick bewegen!", 100, 50, 6);
}



// Funktion um Vorzeichen zu finden
int sgn(int val) {
  if (val < 0) return -1;
  if (val == 0) return 0;
  return 1;
}


// Dancing Lines wie aus ganz alten "Bildschirmschonern"
int xc0, yc0, sx0, sy0, xc1, yc1, sx1, sy1, tidx; //ein paar Merker...
void sparky()
{
  const int fak = 150, off = 80; //Zufalls Bereich (fak+off) und Offset (Minimum)

  if (xc0 == 0 && yc0 == 0) // Ja mach ich noch besser ;-)
  {
    xc0 = rand() % 4096;
    yc0 = rand() % 4096;
    xc1 = rand() % 4096;
    yc1 = rand() % 4096;
    sx0 = rand() % fak + off;
    sy0 = rand() % fak + off;
    sx1 = rand() % fak + off;
    sy1 = rand() % fak + off;
  }

  // Zufälliges abprallen, nix Physik hier :-)
  xc0 = xc0 + sx0;
  if (xc0 > 4095) sx0 = -(rand() % fak + off);
  if (xc0 <= 0)   sx0 =  (rand() % fak + off);

  yc0 = yc0 + sy0;
  if (yc0 > 4095) sy0 = -(rand() % fak + off);
  if (yc0 <= 0)   sy0 =  (rand() % fak + off);

  xc1 = xc1 + sx1;
  if (xc1 > 4095) sx1 = -(rand() % fak + off);
  if (xc1 <= 0)   sx1 =  (rand() % fak + off);

  yc1 = yc1 + sy1;
  if (yc1 > 4095) sy1 = -(rand() % fak + off);
  if (yc1 <= 0)   sy1 =  (rand() % fak + off);

  moveto(xc0, yc0); //Startpunkt
  lineto(xc1, yc1);

  xc[idx] = xc0; // vorherigen Linien merken
  yc[idx] = yc0;
  xc[idx + 20] = xc1;
  yc[idx + 20] = yc1;
  idx = (idx + 1) % 20; //globaler Index (20 Linien a 2 XY Koordinaten)

  for (int i = 0; i < 20; i++)
  {
    tidx = (idx + i ) % 20;
    moveto(xc[tidx], yc[tidx]);
    lineto(xc[tidx + 20], yc[tidx + 20]);
  }
}



// einfache Lissajous-Figuren, mit Floats, wir hams ja...
// Schöner "Blödsinn" die macht man natürlich mit zwei Frequenzgeneratoren und dem Oszi
void lisa()
{
  const float pi = 3.14159265359;
  float xf = 0.0;
  float yf = 0.0;
  float rad;
  int xx, yy;

  for (int w = 0; w <= 360; w = w + 1)
  {
    rad = w * pi / 180.0;

    // aktuelle Funktion. Faktoren 1.0 und 1.0 ergibt einen Kreis
    xf = sin(rad * 3.0);
    yf = cos(rad * 7.0);

    // anpassen an Kordinaten/Aspekt (hier 4:3) und Integerumrechnung
    xx = int(xf * 768.0) + 2048;
    yy = int(yf * 1024.0) + 2048;
    if (w == 0)
      moveto(xx, yy);
    else
      lineto(xx, yy);
  }
}



int xp;
int vxs = 4; //Geschwindigkeit

// Simple Steady Moving Makey NICHT verwenden (siehe Artikel)
void SimpleMoveMakey()
{
  xp = xp + vxs * wait;
  if (xp >= 2500 || xp <= 0)  vxs = vxs * -1;   // lauernder Fehler :-)
  draw_object(11, 800 + xp, 2000, 10, 0);       // Lauf Makey lauf!
  draw_string(itoa(wait, buf, 10), 200, 200, 10); // Ausgabe wait
  draw_string(itoa(xp, buf, 10), 600, 200, 10); // Ausgabe x Koordinate
  wait = 0;
}



// Steady Moving Makey
void SMoveMakey()
{
  xp = xp + vxs * wait;
  if (xp > 2500 * 128 || xp <= 0)
  {
    xp = xp - vxs * wait;
    vxs = vxs * -1;
  }
  draw_object(11, 800 + (xp / 128), 2000, 10, 0); // Lauf Makey lauf!
  draw_string(itoa(wait, buf, 10), 200, 200, 10);
  draw_string(itoa(xp >> 7, buf, 10), 600, 200, 10);
  wait = 0;
}


// Steady Moving Makeys
void MultiMoveMakey()
{
  if (g[0] == 0)    // Krude Initialisierung
  {
    g[0] = 16;  //Geschwindigkeiten
    g[1] = 32;
    g[2] = 64;
    g[3] = 128;
    g[4] = 256;
  }

  for (int i = 0; i < 5; i++) //über 5 Makeys iterieren
  {
    xc[i] = xc[i] + g[i] * wait;
    if (xc[i] > 2500 * 128 || xc[i] <= 0)
    {
      xc[i] = xc[i] - g[i] * wait;
      g[i] = g[i] * -1;
    }
    draw_object(11, 800 + (xc[i] / 128), 600 + 660 * i, 8, 0); // Lauft Makeys lauft!
  }
  draw_string(itoa(wait, buf, 10), 200, 150, 6);
  wait = 0;
}



