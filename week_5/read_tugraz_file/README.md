# Wir erforschen die TU Graz mit Hilfe von Strings und Streams

In diesem Übungsbeispiel nutzen wir Strings und Streams in C++, um die TU Graz besser kennen zu lernen. Genauer gesagt, werden wir demografische Daten zu den einzelnen Studiengängen untersuchen.

## Lernziele

Ziel dieses Übungsbeispiels ist es, die Verwendung von Strings und Streams zu üben.

## Das Problem

Im [CSV](https://de.wikipedia.org/wiki/CSV_(Dateiformat))-File [`Studierendenstatistik.csv`](./Studierendenstatistik.csv) findest du eine [Statistik der belegten Studien an der TU Graz](https://online.tugraz.at/tug_online/ee/ui/ca2/app/desktop/#/pl/ui/$ctx/Studierendenstatistik.html?$ctx=design=ca2;header=max;lang=de&pAuswertung=8&pGruppierung=1&pSJ=1665&pSemester=S&pVerteilungsschluessel=TRUE). Hier ist für jeden Studiengang die Anzahl an inländischen & internationalen Studierenden sowie die Anzahl an männlichen & weiblichen Studierenden angeführt. Jede Zeile in der CSV-Datei (mit Ausnahme der Ersten) entspricht einem Studiengang und enthält Informationen über diesen. Die Informationen über einen Studiengang sind dabei durch Beistriche (`,`) voneinander getrennt, wie du anhand der folgenden Beispielzeile erkennen kannst.

```
UF 066 649,Masterstudium; Computational Social Systems,11,5,3,3,22
```

Welche Informationen eine Zeile beinhaltet und in welcher Reihenfolge sie aufscheinen, legt die erste Zeile der Datei fest:

```
Studien-ID,Studium,Inland Frauen,Inland Männer,Ausland Frauen,Ausland Männer,gesamt
```

Somit sehen wir in der Beispiel-Zeile oben, dass es im Studiengang mit der ID *UF 066 649* insgesamt 22 Studierende gibt. Davon sind
 - 11 Frauen aus dem Inland,
 - 5 Männer aus dem Inland,
 - 3 Frauen aus dem Ausland und
 - 3 Männer aus dem Ausland.

Außer den in der ersten Zeile der CSV-Datei angeführten Merkmalen eines Studiengangs beinhaltet die CSV-Datei keine weiteren Informationen. Insbesondere fehlen interessante aggregierte Statistiken, wie z. B.

 - welches Studium jenes mit den meisten Studierenden ist oder
 - in welchem Studium der Frauenanteil am geringsten oder höchsten ist. 🙁️

## Deine Lösung

In diesem Übungsbeispiel berechnen wir derartige Statistiken und das Tolle ist, dass der Code dafür bereits fast zur Gänze vom LV-Team zur Verfügung gestellt wurde 😃️

Eine sehr zentrale Rolle spielt die Klasse `Major`, welche Informationen über einen Studiengang zusammenfasst. Diese Klasse ist bereits in [Major.hpp](./Major.hpp) und [Major.cpp](./Major.cpp) implementiert.

Wir haben außerdem bereits eine Klasse namens `Database` für dich erstellt (in [`Database.hpp`](./Database.hpp) und [`Database.cpp`](./Database.cpp)). Diese Klasse verfügt über einen `std::vector` als Attribut, in welchem Studiengänge, das heißt `Major`-Objekte gespeichert sind. Außerdem bietet die Klasse bereits Methoden, die interessante Statistiken zu Studiengängen an der TU Graz ausgeben.

Woher bezieht ein `Database`-Objekt die Informationen über die einzelnen Studiengänge? 🤔️ Das geschieht im Konstruktor, in dem die Methode `parseFile(const string& filename)` aufgerufen wird, welche die Datei `filename` lesen soll. Das Argument `filename` ist in der `main`-Funktion der Name der oben erwähnten CSV-Datei.

Die `parseFile`-Methode ist das Einzige, was im bereitgestellten Code fehlt. In [`Database.cpp`](./Database.cpp)) wirst du einen `TODO`-Kommentar finden, welcher die einzelnen Schritte dieser Methode erklärt.

Ist das Einlesen fertig implementiert, wird dir die Datenbank mitteilen, welches Studium von den meisten Studierenden studiert wird, welcher Studiengang den größten Frauen- oder Männeranteil hat, usw. Viel Spaß beim Erforschen der Daten! 🙂️

> **Tipp:** Für das Einlesen der CSV-Datei bietet sich beispielsweise die [getline](https://www.cplusplus.com/reference/string/string/getline/)-Funktion an.

> **Tipp:** Wandelst du einen String in einen Stringstream um, so kannst du aus diesem wie aus `stdin` einlesen und beispielsweise den Beistrich (**,**) als Delimiter angeben.

## Testen

Du kannst deine Lösung jederzeit testen, indem du in diesem Verzeichnis `make test` aufrufst. Dadurch wird eine Datei namens `testreport.html` erstellt. Sie enthält einen Bericht, der dir zeigt, welche Ausgabe dein Programm produzieren sollte und welche Ausgabe dein Programm produziert. Du erhältst auf diese Weise sofortiges Feedback zu deiner Lösung.

## Lösung

Eine Lösung unserer Tutor\*innen befindet sich im Ordner `solution`. Solltest du Probleme haben, das Übungsbeispiel zu lösen, dann könnte dir diese von uns bereitgestellte Lösung helfen. Bedenke jedoch, dass du den größtmöglichen Lerneffekt nur dann erzielst, wenn du wirklich versuchst, das Übungsbeispiel selbst zu lösen.

Im Ordner `solution` gibt es auch ein Makefile. Das heißt, dass du im Ordner `solution` ebenfalls `make test` ausführen kannst. Damit wird die Lösung unserer Tutor\*innen getestet.

## Mitwirkende an diesem Übungsbeispiel

- Marlene Jüttler
- Aleksandar Karakaš
- Florian Hager (Unterstützung bei Test Cases 🙂️)

