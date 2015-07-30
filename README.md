# H1
Centrifuge Safety code

This code is to control the speed and safety of the Physics 1D Centrifuge. Can be re-used for other Electronic Speed Controller systems.

Call this function when you need to vary the limit and still read the values from the variable resistor.
'''C
int safety_function(int val, int limit){
  if(val < limit){
    myservo.write(val);
    return val;
  }
  else{
    myservo.write(limit);
    return  limit;
  }

}
'''

Thanks for those who have sacrificed for this project :3