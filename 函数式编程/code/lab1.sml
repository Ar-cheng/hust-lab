print("1.2\n");
fun mult [ ] = 1 
	| mult (x::l) = x * mult (l);
val list1 =[1,2,3,4];
val res1 = mult(list1);

print("\n1.3");
fun Mult [ ] = 1 
	| Mult (r::R) = mult(r)*Mult(R);
val list2 =[[1,2,3],[4,5]];
val res2 = Mult(list2);

print("\n1.4");
fun mult' ([ ], a) = a
	| mult' (x :: L, a) = mult' (L, x * a);
fun Mult' ([ ], a) = a
    | Mult' (r::R, a) = Mult(R) * mult'(r,a);
val list3 = ([[1,2,3],[4,5]],6);
val res3 = Mult'(list3);

print("\n1.5\n");
fun double (0 : int) : int = 0
    | double n = 2 + double (n - 1);
fun square(0:int):int =0
	| square(x) = square(x-1)+double(x-1)+1;
val num = 5;
val res4 = square(num);

print("\n1.6\n");
fun divisibleByThree(x:int):bool =
		if x=0 then true 
		else if x=1 then false 
		else if x=2 then false 
		else divisibleByThree(x-3);
val num = 14;
val res5 = divisibleByThree(num);

print("\n1.7\n");
fun evenP (0 : int) : bool = true
  	    | evenP 1 = false
  	    | evenP n = evenP(n - 2);
val num = 13;
val res6 = evenP(num);

print("\n计卓-U20174480-朱志成");