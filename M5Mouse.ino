#include <M5Cardputer.h>
#include <BleMouse.h>

BleMouse bleMouse;
uint8_t speed = 10;
bool connected = false;

void setup()
{
  M5Cardputer.begin(true);
  bleMouse.begin();
  M5Cardputer.Display.setRotation(1);
  M5Cardputer.Display.setCursor(0, 0);
  M5Cardputer.Display.setTextSize(3);
  M5Cardputer.Display.println("BLE Mouse");
  M5Cardputer.Display.println("Start...");
  M5Cardputer.Display.display();
  delay(1000);
}

void loop()
{
  M5Cardputer.update();

  if (connected != bleMouse.isConnected())
  {
    M5Cardputer.Display.clear();
    connected = bleMouse.isConnected();
  }

  M5Cardputer.Display.setCursor(0, 0);
  M5Cardputer.Display.setTextSize(3);
  M5Cardputer.Display.println("BLE Mouse");

  if (!bleMouse.isConnected())
  {
    M5Cardputer.Display.println("Wait...");
  }
  else
  {
    bleMouse.setBatteryLevel(M5Cardputer.Power.getBatteryLevel());
    M5Cardputer.Display.println("Connected");
    M5Cardputer.Display.printf("Speed: %d  \n", speed);
  }

  auto x = M5Cardputer.Display.getCursorX();
  auto y = M5Cardputer.Display.getCursorY();
  M5Cardputer.Display.println("                      ");

  M5Cardputer.Display.setCursor(x, y);
  if (M5Cardputer.Keyboard.isKeyPressed(';'))
  {
    if (M5Cardputer.Keyboard.isKeyPressed(KEY_FN))
    {
      bleMouse.move(0, 0, -1);
      M5Cardputer.Display.println("Wheel + ^");
    }
    else
    {
      bleMouse.move(0, -speed);
      M5Cardputer.Display.println("^");
    }
  }
  else if (M5Cardputer.Keyboard.isKeyPressed(','))
  {
    bleMouse.move(-speed, 0);
    M5Cardputer.Display.println("<");
  }
  else if (M5Cardputer.Keyboard.isKeyPressed('.'))
  {
    if (M5Cardputer.Keyboard.isKeyPressed(KEY_FN))
    {
      bleMouse.move(0, 0, 1);
      M5Cardputer.Display.println("Wheel + v");
    }
    else
    {
      bleMouse.move(0, speed);
      M5Cardputer.Display.println("v");
    }
  }
  else if (M5Cardputer.Keyboard.isKeyPressed('/'))
  {
    bleMouse.move(speed, 0);
    M5Cardputer.Display.println(">");
  }

  M5Cardputer.Display.setCursor(x, y);

  if (M5Cardputer.Keyboard.isChange())
  {
    if (M5Cardputer.Keyboard.isKeyPressed('a'))
    {
      bleMouse.click(MOUSE_LEFT);
      M5Cardputer.Display.println("L");
    }
    else if (M5Cardputer.Keyboard.isKeyPressed('s'))
    {
      bleMouse.click(MOUSE_RIGHT);
      M5Cardputer.Display.println("R");
    }
    else if (M5Cardputer.Keyboard.isKeyPressed(KEY_ENTER))
    {
      bleMouse.click(MOUSE_FORWARD);
      M5Cardputer.Display.println("F");
    }
    else if (M5Cardputer.Keyboard.isKeyPressed(KEY_BACKSPACE))
    {
      bleMouse.click(MOUSE_BACK);
      M5Cardputer.Display.println("B");
    }

    for (auto key : M5Cardputer.Keyboard.keyList())
    {
      auto i = M5Cardputer.Keyboard.getKeyValue(key).value_first;
      if (i >= '1' && i <= '9')
      {
        speed = (i - '1' + 1) * 5;
      }
      if (i == '0')
      {
        speed = 10 * 5;
      }
    }
  }

  M5.Display.display();
}
