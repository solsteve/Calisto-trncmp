#/ =======================================================================================
def load( argv, pre=None ):
    #/ -----------------------------------------------------------------------------------
    if ( None == pre ):
        cli = {}
    else:
        cli = pre
        
    fileNumber = 1

    for token in argv[1:]:
        kvp = token.split('=')
        if ( 1 == len(kvp) ):
            key = 'file%d' % (fileNumber,)
            fileNumber += 1
            value = kvp[0].strip()
        elif ( 2 == len(kvp) ):
            key   = kvp[0].strip()
            value = kvp[1].strip()
        elif ( 2 < len(kvp) ):
            key   = kvp[0].strip()
            value = '='.join(kvp[1:]).strip()
        else:
            raise 'CLI Parse error'
        cli[key] = value
    return cli

    
