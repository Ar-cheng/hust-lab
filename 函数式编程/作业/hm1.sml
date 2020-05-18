fun zip ( (x::L1, y::L2) : string list * int list ) : (string * int) list = (x,y)::zip(L1,L2)
	|zip ( _ , [ ] ) = []
	|zip ( [ ] ,_ ) = [];

zip(["abc","def"],[1,2,3]);


fun unzip ( [ ]: (string * int ) list ) : string list * int list = ([],[])
	|unzip( (x,y)::L ) =	
		let 
			val (L1,L2) = unzip(L)
		in
			(x::L1,y::L2)
		end;

unzip(zip(["abc","def"],[1,2,3]));