#!/usr/bin/python3
#/ ========================================================= BEGIN FILE =====

import sys
import numpy as np
import numpy.random as nr

NUMB = { 'A':1, '2':2, '3':3, '4':4, '5':5, '6':6, '7':7, '8':8, '9':9, '1':10, 'J':11, 'Q':12, 'K':13 }

SUIT = { 's':0, 'h':1, 'c':2, 'd':3 }


#/ ==========================================================================
def Numbers( list ):
    #/ ----------------------------------------------------------------------
    N = []
    for x in list:
        N.append( NUMB[x[0]] )
    return N


#/ ==========================================================================
def Suits( list ):
    #/ ----------------------------------------------------------------------
    N = []
    for x in list:
        N.append( SUIT[x[-1]] )
    return N


#/ ==========================================================================
def max_index( seq ):
    #/ ----------------------------------------------------------------------
    max_idx = 0
    max_val = seq[max_idx]
    n       = len( seq )
    i = 1
    while( i<n ):
        if ( seq[i] > max_val ):
            max_val = seq[i]
            max_idx = i
        i += 1
    return max_idx


#/ ==========================================================================
def RunHist( seq ):
    #/ ----------------------------------------------------------------------
    n = len(seq)
    m = max(seq)
    H = (m+1)*[0]
    for x in seq:
        H[x] += 1
    return H
    

#/ ==========================================================================
def decSubSeq( list ):
    #/ ----------------------------------------------------------------------
    n = len(list)
    count = 1;
    prev  = list[0]
    i = 1
    while (i < n ):
        x = list[i]
        if ( 1 == (prev - x) ):
            count += 1
            i     += 1
            prev   = x
        else:
            return (count,i)
    return (count,None)


#/ ==========================================================================
def incSubSeq( list ):
    #/ ----------------------------------------------------------------------
    n = len(list)
    count = 1;
    prev  = list[0]
    i = 1
    while (i < n ):
        x = list[i]
        if ( 1 == (x - prev) ):
            count += 1
            i     += 1
            prev   = x
        else:
            return (count,i)
    return (count,None)


#/ ==========================================================================
def sameSubSeq( list ):
    #/ ----------------------------------------------------------------------
    n = len(list)
    count = 1;
    prev  = list[0]
    i = 1
    while (i < n ):
        x = list[i]
        if ( x == prev ):
            count += 1
            i     += 1
            prev   = x
        else:
            return (count,i)
    return (count,None)


#/ ==========================================================================
def sameRunLength( list ):
    #/ ----------------------------------------------------------------------
    sub = []
    idx = 0
    while( True ):
        c, n =  sameSubSeq(list[idx:])
        sub.append(c)
        if ( None == n ):
            return sub
        idx += n

        
#/ ==========================================================================
def incRunLength( list ):
    #/ ----------------------------------------------------------------------
    sub = []
    idx = 0
    while( True ):
        c, n =  incSubSeq(list[idx:])
        sub.append(c)
        if ( None == n ):
            return sub
        idx += n

        
#/ ==========================================================================
def decRunLength( list ):
    #/ ----------------------------------------------------------------------
    sub = []
    idx = 0
    while( True ):
        c, n =  decSubSeq(list[idx:])
        sub.append(c)
        if ( None == n ):
            return sub
        idx += n

        
#/ ==========================================================================
def Flip():
    #/ ----------------------------------------------------------------------
    if ( nr.rand() < 0.5 ):
        return False
    return True


#/ ==========================================================================
def MergeCards( A, B ):
    #/ ----------------------------------------------------------------------
    na = len(A)
    nb = len(B)
    n  = min(na,nb)
    i=0
    list = []

    if ( Flip() ):
        while ( i<n ):
            list.append( A[i] )
            list.append( B[i] )
            i += 1
    else:
        while ( i<n ):
            list.append( B[i] )
            list.append( A[i] )
            i += 1
        
    if ( Flip() ):
        for x in A[n:]:
            list.append( x )
        for x in B[n:]:
            list.append( x )
    else:
        for x in B[n:]:
            list.append( x )
        for x in A[n:]:
            list.append( x )

    return list


#/ ==========================================================================
def CutDeck( A ):
    #/ ----------------------------------------------------------------------
    n = int(len(A) / 2)
    x = A[:n]
    y = A[n:]
    return ( x, y )


#/ ==========================================================================
def PullMiddleCards( A ):
    #/ ----------------------------------------------------------------------
    n = len(A)
    
    n1 = int(n / 4)
    n2 = int(( n * 3 ) / 4)
        
    A[:n1]
    A[n1:n2]
    A[n2:]

    if ( Flip() ):
        return ( A[n1:n2], A[:n1] + A[n2:] )
    return ( A[:n1] + A[n2:], A[n1:n2] )


#/ ==========================================================================
def FivePiles( A ):
    #/ ----------------------------------------------------------------------

    bins = [ [], [], [], [], [] ]

    i=0
    for x in A:
        bins[i].append(x)
        i = (i + 1) % 5

    return bins[1] + bins[3] + bins[2] + bins[0] + bins[4]


#/ ==========================================================================
def DisplayCards( A ):
    #/ ----------------------------------------------------------------------

    sys.stdout.write( '%s' % ( A[0], ) )

    for x in A[1:]:
        sys.stdout.write( ' %s' % ( x, ) )

    sys.stdout.write( '\n' )


#/ ==========================================================================
def CutFold( deck1 ):                                            # Cut - Fold
    #/ ----------------------------------------------------------------------
    (Da, Db) = CutDeck( deck1 )
    return MergeCards( Da, Db )
 
#/ ==========================================================================
def PullFold( deck1 ):                                          # Pull - Fold
    #/ ----------------------------------------------------------------------
    (Da, Db) = PullMiddleCards( deck1 )
    return MergeCards( Da, Db )

#/ ==========================================================================
def CutPullFold( deck1 ):                                 # Cut - Pull - Fold
    #/ ----------------------------------------------------------------------
    (Da, Db) = CutDeck( deck1 )
    (Da, Db) = PullMiddleCards( Da + Db )
    return MergeCards( Da, Db )

#/ ==========================================================================
def OriginalShuffle( deck1 ):
    #/ ----------------------------------------------------------------------
    n = len(deck1)
    k = int(( n * ( np.log(n) / np.log(2.0) ) / 2.0 ) + 0.5 )
    i = 0
    while( i < k ):
        a = nr.randint(n)
        b = nr.randint(n)
        if ( a != b ):
            i += 1
            temp     = deck1[a]
            deck1[a] = deck1[b]
            deck1[b] = temp
    return deck1
    
        
#/ ==========================================================================
def KnuthShuffle( deck ):
    #/ ----------------------------------------------------------------------
    for i in range(len(deck)-1, 0, -1):
        j = nr.randint(i)
        temp    = deck[i]
        deck[i] = deck[j]
        deck[j] = temp
        
    return deck
    
        
#/ ==========================================================================
def Report( deck ):
    #/ ----------------------------------------------------------------------
    DisplayCards(deck)
    print("value")
    print( '  same ', RunHist(sameRunLength(Numbers(deck))) )
    print( '  up   ', RunHist(incRunLength(Numbers(deck))) )
    print( '  down ', RunHist(decRunLength(Numbers(deck))) )
    print("suit")
    print( '  same ', RunHist(sameRunLength(Suits(deck))) )

#/ ==========================================================================
def MakeDeck():
    #/ ----------------------------------------------------------------------
    numb = [ 'A', '2', '3', '4', '5', '6', '7', '8', '9', '10', 'J', 'Q', 'K' ]
    suit = [ 's', 'h', 'c', 'd' ]

    deck = []
    
    for s in suit:
        for n in numb:
            deck.append( n+s )

    return deck
   
       
#/ ==========================================================================
def main( argc, argv ):
    #/ ----------------------------------------------------------------------

    nr.seed()

    print ( '\n===========================================================' )
    deck = MakeDeck()
    Report( deck )

    print ( '===========================================================' )
    for i in range(10):
        print ( '\n----- %d ---------------------------------' % (i+1,) )
        deck = OriginalShuffle( deck )
        Report(deck)
        
    print ( '\n===========================================================' )
    deck = MakeDeck()
    Report( deck )

    print ( '===========================================================' )
    for i in range(10):
        print ( '\n----- %d ---------------------------------' % (i+1,) )
        deck = KnuthShuffle( deck )
        Report(deck)
        
    return 0

#/ ==========================================================================
if ( '__main__'==__name__ ):
    sys.exit( main( len(sys.argv), sys.argv ) )
#/ =========================================================== END FILE =====
