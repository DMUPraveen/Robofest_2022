while( input("Continue :") != ' '):
    current_angle = float( input("Current Angle :") )
    target_angle = float( input("Target Angle :") )

    print( current_angle , target_angle , end = '\t')
    difference = abs( target_angle - current_angle )

    if difference <= 180:
        if target_angle >= current_angle:
            print( difference )

        else:
            print( -difference )

    else:
        if target_angle > current_angle:
            print( difference - 360 )

        else:
            print( -difference + 360 )