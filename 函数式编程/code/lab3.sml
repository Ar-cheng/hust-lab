print("LAB3.1\n");
fun sqrt(x:int):int = x * x;
fun thenAddOne( (f:int->int), (x:int) ):int = f x + 1;
val exp1 = 5;
thenAddOne(sqrt,exp1);

print("\nLAB3.2~3.3\n");
fun mapList (f: 'a -> 'b, [] : 'a list)  : 'b list = []
    |mapList (f, x::L) = (f x)::(mapList (f, L));
fun mapList' (f : 'a -> 'b) ([] : 'a list) : 'b list = []
	|mapList'(f)(x::L) = (f x)::(mapList' f L);
val exp2 = [1,2,3,4,5];
mapList(sqrt,exp2);
val exp3 = [1,3,5,7,9];
mapList' sqrt exp2;

print("\nLAB3.4\n");
fun findOdd([] : int list): int option = NONE
  | findOdd(x::L) = if (x mod 2)=1 then SOME x else findOdd L;
val exp4 = [1,8,3,4,6];
findOdd(exp4);

print("\nLAB3.5\n");
fun subsetSumOption ([] : int list, n : int) : int list option = NONE
  | subsetSumOption (l , 0 ) = SOME []
  | subsetSumOption (x::L, sum) =
    if subsetSumOption(L, sum-x) = NONE 
    then 
      subsetSumOption(L, sum)
    else 
      SOME ( x::( valOf( subsetSumOption(L, sum-x) ) ) );
val exp5 = [1,2,3,4,5];
val tar = 7;
subsetSumOption(exp5,tar);

print("\nLAB3.6\n");
fun exists (p : 'a -> bool) (l : 'a list) : bool =
    foldl (fn (a,b) => p a orelse b)  false l;
fun forall (p : 'a -> bool) (l : 'a list) : bool =
    foldl (fn (a,b) => p a andalso b)  true l;
fun p(n:int):bool= if n>4 then true else false;
val exp6_1 = [1,2,3,4];
exists p exp6_1;
val exp6_2 = [5,6,7,8];
forall p exp6_2;

print("\nLAB3.7\n");
datatype 'a tree = Empty | Node of 'a tree * 'a * 'a tree;

fun split(l: int list) =
        let
          val m = (length l) div 2
          val L = (List.take (l,m))
          val x :: R = (List.drop (l,m))
        in
          (L, x, R)
    end;

fun listToTree([]:int list):int tree = Empty
  | listToTree(L) =
    let
      val (l,x,r) = split(L)
    in
      Node(listToTree(l),x,listToTree(r))
    end;

fun treeFilter (p : 'a -> bool ) (Empty) : 'a option tree = Empty
  | treeFilter (p) (Node (l, x, r)) =
    let
      val y = if p x then SOME x else NONE
    in
      Node (treeFilter p l, y, treeFilter p r)
    end;

val exp7=listToTree([1,2,3,4,5]);
treeFilter p exp7;