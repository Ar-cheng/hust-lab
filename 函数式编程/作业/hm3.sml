(* toInt: int -> int list -> int *)
fun toInt (b:int) = 
	let fun baseToInt([]:int list):int = 0
		|baseToInt(L) = 
			let
				val len = length L
				val L1 = List.take(L,len -1)
				val y::L2 = List.drop(L,len -1)
			in
				y + b * baseToInt(L1)
			end
	in baseToInt end;

(* toBase: int -> int -> int list  *)
fun toBase (b:int) =
	let fun intToBase(0:int):int list = [0]
		|intToBase(x) = 
			let
				fun helper(n:int, L:int list):int list = 
				case n of
					0 => L
					|_ => helper(n div b , (n mod b)::L )
			in 
				helper(x,[])
			end
	in intToBase end;

(* convert: int * int -> int list -> int list *)
fun convert (b1:int, b2:int) =
	let 
		fun B1ToB2( L:int list ):int list = toBase b2 ( toInt b1 L )
	in 
		B1ToB2 
	end;
	
val exp1 = toInt 3 (convert(2, 3) [1,0,0,1,1]);
val exp2 = toInt 2 [1,0,0,1,1];