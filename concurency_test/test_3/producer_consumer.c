

int counter1, counter2
int m1, m2


while (1) {
  
  lock(m1)
  if (counter1 < n) {
    counter1++;
  } else {
    unlock(m1)
    continue;
  }
  unlock(m1)

  item = produce();

  lock(m2)
  insert(item)
  counter2++;
  unlock(m2)
}

while (1) {

  lock(m2)
  item = remove()
  counter1--;
  lock(m1)
  counter2--
  unlock(m1)
  unlock(m2)

}