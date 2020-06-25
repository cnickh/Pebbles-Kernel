#include <keyboard_driver.h>


kbuf_t* kbuf; //create a pointer to a struct to hold keystroke data


void init_kbuf(){
  kbuf = calloc(1,sizeof(kbuf_t));
  kbuf->size = KEY_BUF_SIZE;
  kbuf->buf = calloc(kbuf->size,sizeof(char));
  kbuf->tail = kbuf->head = 0;
}

void add_to_kbuf(char ch){
  kbuf->buf[kbuf->tail++ % kbuf->size] = ch;//put keystroke in buffer
}

int readchar(){

  if(kbuf->head < kbuf->tail){

    char ch = kbuf->buf[kbuf->head++ % kbuf->size]; //get keyboard data FIFO
    kh_type augchar = process_scancode(ch); //Use the provide function to decode

    if(KH_HASDATA(augchar) && KH_ISMAKE(augchar)){ //verify the key was pressed
      return KH_GETCHAR(augchar);

    } else{
      return -1;
    }


  } else {
    return -1;
  }


}
