(* PrefixSum: int list -> int list *)
fun prefixsum [] = []
	|prefixsum [x] = [x]
	|prefixsum (x::y::L) = x::prefixsum( (x+y)::L );

(* fastPrefixSum: int list -> int list *)
fun fastprefixsum(Z:int list):int list = 
	let 
		fun helper(A:int list , B:int list):int list = 
			case (A,B) of
				([],_) => B
				|(x::L,[]) => helper(L,[x]) 
				|(x::L,_) => 
					let 
						val len = length B
						val y::R = List.drop(B,len -1)
					in 
						helper(L,B@[x+y]) 
					end
	in
		helper(Z,[])
	end;

val exp1 = [1,2,3,4,5];
prefixsum exp1;
fastprefixsum exp1;

(* treecompare: tree * tree -> order *) 
datatype tree = Empty | Node of tree *int *tree;
fun treecompare (Empty :tree, _ :tree):order = GREATER
	|treecompare(_,Empty) = LESS
	|treecompare(Node(_,x,_),Node(_,y,_)) = Int.compare(x,y);
	
(* SwapDown: tree -> tree *) 
fun SwapDown(Empty:tree):tree = Empty 
	|SwapDown(Node(Empty,x,Empty)) = Node(Empty,x,Empty) 
	|SwapDown(Node(t1,x,t2))= 
		case treecompare(t1,t2) of 
			LESS => 
				let 
					val Node(l,y,r) = t1 
				in 
					case Int.compare(x,y) of 
						GREATER => Node(SwapDown(Node(l,x,r)),y,t2) 
						| _ => Node(t1,x,t2)
				end 
			| _ =>
				let 
					val Node(l,y,r) = t2 
				in 
					case Int.compare(x,y) of 
						GREATER => Node(t1,y,SwapDown(Node(l,x,r))) 
						| _ => Node(t1,x,t2)
				end;

(* heapify : tree -> tree *)
fun heapify(Empty:tree):tree = Empty 
	|heapify(Node(t1,x,t2)) = 
		SwapDown(Node(heapify(t1),x,heapify(t2)));

val exp2 = Node( Node( Node(Empty,1,Empty), 3, Node(Empty,2,Empty)), 7,
				Node( Node(Empty,4,Empty), 6, Node(Empty,5,Empty))  ); 

heapify(exp2);  