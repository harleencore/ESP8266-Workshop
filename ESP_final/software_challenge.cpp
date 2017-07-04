String redVal = getValue(myString, ':', 0);
String greenVal = getValue(myString, ':', 1);
String blueVal = getValue(myString, ':', 2);

Serial.println("RED:" + redVal);
Serial.print("GREEN:" + greenVal);
Serial.print("BLUE:" + blueVal);

int redValue = stringToNumber(redVal);
int greenValue = stringToNumber(greenVal);
int blueValue = stringToNumber(blueVal);

Serial.println(setColour(redValue, greenValue, blueValue))


String getValue(String data, char separator, int index)
{
    int found = 0;
    int strIndex[] = { 0, -1 };
    int maxIndex = data.length() - 1;

    for (int i = 0; i <= maxIndex && found <= index; i++) {
        if (data.charAt(i) == separator || i == maxIndex) {
            found++;
            strIndex[0] = strIndex[1] + 1;
            strIndex[1] = (i == maxIndex) ? i+1 : i;
        }
    }
    return found > index ? data.substring(strIndex[0], strIndex[1]) : "";
}
