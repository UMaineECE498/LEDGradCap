#include <stdint.h>
#include <util/delay.h>

#include "system.h"
#include "ledRoutines.h"


/*
 *  This assumes colors are all at 0;
 */
void simpleFade(uint8_t *colorToFade, uint8_t inOrOut)
{
    uint8_t i,j;

    if (inOrOut == IN)
    {
        for (i=0; i<8; i++)
        {
            *(colorToFade+i) = 0;
        }
    }
    else
    {
        for (i=0; i<8; i++)
        {
            *(colorToFade+i) = 64;
        }
    }

    //  Max value for any color is 64
    for (j=0; j<64; j++)
    {
		send_leds(red, green, blue);

        for (i=0; i<8; i++)
        {
            *(colorToFade+i) += inOrOut;
        }

		_delay_ms(50);
    }
}
#if 0
/*
 *  This version's too big.
 */
void fade(uint8_t *red, uint8_t *green, uint8_t *blue, uint8_t inOrOut)
{
	uint8_t i, j;
    uint8_t tr[8] = { 0 };	// Red values
    uint8_t tg[8] = { 0 };	// Green values
    uint8_t tb[8] = { 0 };	// Blue values


    if (inOrOut == IN)
    {
        for (i=0; i<8; i++)
        {
            *(tr+i) = *(red+i);
            *(tg+i) = *(green+i);
            *(tb+i) = *(blue+i);
        }
    }
    else
    {
        for (i=0; i<8; i++)
        {
            *(tr+i) = 0;
            *(tg+i) = 0;
            *(tb+i) = 0;
        }
    }

    //  Max value for any color is 128
    for (j=0; j<128; j++)
    {
		send_leds(tr, tg, tb);

        for (i=0; i<8; i++)
        {
            if (inOrOut == IN)
            {
                if ( *(tr+i) < *(red+i) )
                {
                    *(tr+i) += 1;
                }
                if ( *(tg+i) < *(green+i) )
                {
                    *(tg+i) += 1;
                }
                if ( *(tb+i) < *(blue+i) )
                {
                    *(tb+i) += 1;
                }
            }
            else
            {
                if ( *(tr+i) > 0 )
                {
                    *(tr+i) -= 1;
                }
                if ( *(tg+i) > 0 )
                {
                    *(tg+i) -= 1;
                }
                if ( *(tb+i) > 0 )
                {
                    *(tb+i) -= 1;
                }
            }
        }

		_delay_ms(50);
    }
}
#endif
