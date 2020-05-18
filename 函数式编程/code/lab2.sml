print("lab2.1\n");
fun reverse [] = []
	|reverse (a::L) = (reverse L) @ [a] ;
val exp1 = [1,2,3];
reverse(exp1);

fun reverse'(L:int list): int list =
	let
		fun helper(L:int list , A:int list):int list =
			case L of
				[] => A
				| x::R => helper(R, x::A)
	in
		helper(L,[])
	end;
reverse(exp1);

print("\nlab2.2\n");
fun interleave(A : int list , B : int list) : int list = 
	case (A , B) of
	(_,[]) => A
	|([],_) => B
	|(a::L1,b::L2) => a::b::interleave(L1,L2);
val exp21 = [1,2,3];
val exp22 = [4,5,6];
interleave(exp21,exp22);

print("\nlab2.3\n");
datatype tree = Empty | Node of tree *int *tree;

fun split(l: int list) =
      	let
        	val m = (length l) div 2
        	val L = (List.take (l,m))
        	val x :: R = (List.drop (l,m))
      	in
        	(L, x, R)
		end;

fun listToTree([]:int list):tree = Empty
	| listToTree(L)=
		let
			val (l,x,r) = split(L)
		in
			Node(listToTree(l),x,listToTree(r))
		end;

val exp3=[1,2,3,4,5];
listToTree(exp3);

print("\nlab2.4\n");
fun revT (Empty : tree):tree = Empty
  | revT (Node(l,x,r)) = Node (revT (r), x , revT (l));
val exp4=listToTree([1,2,3]);
revT(exp4);

print("\nlab2.5\n");
fun binarySearch(Empty:tree, i: int): bool = false
	|binarySearch(Node(l,x,r), i) =
	case Int.compare(x,i) of
		GREATER => binarySearch(l,i)
  	 	| EQUAL => true
    	| LESS => binarySearch(r,i)
val exp5 = listToTree([1,2,3,4,5]);
binarySearch(exp5,5);