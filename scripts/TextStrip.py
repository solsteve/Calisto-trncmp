#!/usr/bin/python3
#/ ====================================================================== BEGIN FILE =====
#/ **                                                                                   **
#/ **  This file is part of the TRNCMP Research Library, `Callisto' (formerly SolLib.)  **
#/ **                                                                                   **
#/ **  Copyright (c) 2019, Stephen W. Soliday                                           **
#/ **                      stephen.soliday@trncmp.org                                   **
#/ **                      http:#/research.trncmp.org                                   **
#/ **                                                                                   **
#/ **  -------------------------------------------------------------------------------  **
#/ **                                                                                   **
#/ **  Callisto is free software: you can redistribute it and/or modify it under the    **
#/ **  terms of the GNU General Public License as published by the Free Software        **
#/ **  Foundation, either version 3 of the License, or (at your option)                 **
#/ **  any later version.                                                               **
#/ **                                                                                   **
#/ **  Callisto is distributed in the hope that it will be useful, but WITHOUT          **
#/ **  ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS    **
#/ **  FOR A PARTICULAR PURPOSE. See the GNU General Public License for more details.   **
#/ **                                                                                   **
#/ **  You should have received a copy of the GNU General Public License along with     **
#/ **  Callisto. If not, see <https:#/www.gnu.org/licenses/>.                           **
#/ **                                                                                   **
#/ =======================================================================================

import sys, re

import CLIMap


#/ =======================================================================================
def CountWords( inF ):
    #/ -----------------------------------------------------------------------------------
    count = {}
    
    for raw in inF:
        words = raw.split()
        for token in words:
            word = ''.join(c for c in token if (c==' ' or c.isalpha())).strip().upper()
            try:
                c = count[word]
                count[word] = c + 1
            except KeyError:
                count[word] = 1
    return count

#/ =======================================================================================
def TwoGrams( words ):
    #/ -----------------------------------------------------------------------------------
    gram = {}
    
    for word in words:
        n = words[word]
        m = len(word)
        if ( 1 < m ):
            for i in range(m-1):
                g = word[i] + word[i+1]
                try:
                    x = gram[g]
                    gram[g] = x + n
                except KeyError:
                    gram[g] = n
    return gram

#/ =======================================================================================
def ThreeGrams( words ):
    #/ -----------------------------------------------------------------------------------
    gram = {}
    
    for word in words:
        n = words[word]
        m = len(word)
        if ( 2 < m ):
            for i in range(m-2):
                g = word[i] + word[i+1] + word[i+2]
                try:
                    x = gram[g]
                    gram[g] = x + n
                except KeyError:
                    gram[g] = n
    return gram


#/ =======================================================================================
def FourGrams( words ):
    #/ -----------------------------------------------------------------------------------
    gram = {}
    
    for word in words:
        n = words[word]
        m = len(word)
        if ( 3 < m ):
            for i in range(m-3):
                g = word[i] + word[i+1] + word[i+2] + word[i+3]
                try:
                    x = gram[g]
                    gram[g] = x + n
                except KeyError:
                    gram[g] = n
    return gram

#/ =======================================================================================
def FiveGrams( words ):
    #/ -----------------------------------------------------------------------------------
    gram = {}
    
    for word in words:
        n = words[word]
        m = len(word)
        if ( 4 < m ):
            for i in range(m-4):
                g = word[i] + word[i+1] + word[i+2] + word[i+3] + word[i+4]
                try:
                    x = gram[g]
                    gram[g] = x + n
                except KeyError:
                    gram[g] = n
    return gram








        
#/ =======================================================================================
def usage( pn, msg=None ):
    #/ -----------------------------------------------------------------------------------
    if ( None != msg ):
        sys.stderr.write( '\n%s\n' % (msg,) )

    sys.stderr.write( """
USAGE: %s [options]
   if = input file
   of = output file

Example: %s if=input.dat of=output.dat

""" % (pn,pn,) )

    return 0

#/ =======================================================================================
def main( argc, argv ):
    #/ -----------------------------------------------------------------------------------

    cli = CLIMap.load( argv )

    try:
        if ( 'help' == cli['file0'] ):
            usage( argv[0] )
    except:
        pass

    try:
        inF          = open( cli['if'], 'r' )
        closeInFile  = True
    except KeyError:
        inF          = sys.stdin
        closeInFile  = False

    try:
        outF          = open( cli['of'], 'w' )
        closeOutFile  = True
    except KeyError:
        outF          = sys.stdout
        closeOutFile  = False

    words = CountWords( inF )

    if ( closeInFile ):
        inF.close()

    for k in words:
        n = words[k]
        if ( 1 < n ):
            outF.write('%s %d\n' % (k,n,) )

    outF.write( '# ----- two grams ------------------------------\n' )
        
    G2 = TwoGrams( words )

    for k in G2:
        n = G2[k]
        if ( 1 < n ):
            outF.write('%s %d\n' % (k,n,) )
    
    outF.write( '# ----- three grams ------------------------------\n' )
        
    G3 = ThreeGrams( words )

    for k in G3:
        n = G3[k]
        if ( 1 < n ):
            outF.write('%s %d\n' % (k,n,) )
    
    outF.write( '# ----- four grams ------------------------------\n' )
        
    G4 = FourGrams( words )

    for k in G4:
        n = G4[k]
        if ( 1 < n ):
            outF.write('%s %d\n' % (k,n,) )
    
    outF.write( '# ----- five grams ------------------------------\n' )
        
    G5 = FiveGrams( words )

    for k in G5:
        n = G5[k]
        if ( 1 < n ):
            outF.write('%s %d\n' % (k,n,) )
    
    if ( closeOutFile ):
        outF.close()
    
    return 0

#/ =======================================================================================
if ( '__main__'==__name__ ): sys.exit( main( len(sys.argv), sys.argv ) )
#/ ======================================================================== END FILE =====
