# Testing speed of function "Transport"
Dmitry used <chrono> to write the time of compiling 50k,100k,500k iterations and Alexander(me) made this markdown file with table of iterations-time.

### Time(sec) of compiling for diffrent graphs.
| Iterations | Chain | Clique |
| ------ | ------ | ------ |
| 50.000 | 2.26 | 12.03 |
| 100.000 | 4.33 | 21.16 | 
| 500.000 | 20.92 | 103.39 |
С английским не всё впорядке пока что, поэтому перейду на русский. :)
В цепи работает быстрее, т.к. путь от одной вершины к другой всегда один. Соответственно, при поиске кратчайшего пути(который мы делаем за итерацию хотя бы раз) мы получим асимптотику O(N). В полном всё чуть сложнее и нам придётся найти кратчайший путь за O(NlogN). Вершин мы брали 100 так, что log(100) ~ 7.4. Время на полном графе увеличилось в 5 раз, что близко к log(100). Поэтому отсюда такие показатели.
##### Alexander Biliba 
##### Dmitry Rudovich