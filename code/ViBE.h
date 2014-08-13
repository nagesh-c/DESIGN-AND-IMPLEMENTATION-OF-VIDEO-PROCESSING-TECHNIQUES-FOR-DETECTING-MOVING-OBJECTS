/* defines parameters for background subtraction algorithm
* methods to form initial sample history and to perform background subtraction
*/
#ifndef __VIBE_H__
#define __VIBE_H__

//Number of samples
#define N 20

//Radius of sphere
#define R 20

//amount of random sampling
#define RANDOM_SAMPLE 16

//minimum cardinality
#define MIN_CARD 2

//foreground and background identifiers
const uint8_t background=0;
const uint8_t foreground=255;

// background model
extern uint8_t *samples;

/*called once to build background model. One frame builds 20 sample history
* per pixel by copying neighbouring values randomly
*/
void init_background_model(uint8_t *image,int width,int height);

// to get foreground image 0 for background 255 for foreground
// background model to be initalized first
void background_subtract(uint8_t *image,uint8_t *segMap,int width,int height);

#endif /* end of ViBE.h */
