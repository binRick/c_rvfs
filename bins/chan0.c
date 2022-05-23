// MESON_BIN_ENABLED=true
#include "../src/includes.c"


int main(){
  // Initialize buffered channel with a capacity of 2.
  chan_t *chan = chan_init(2);

  // Send up to 2 values without receiver.
  log_info("Sending....");
  chan_send(chan, "buffered");
  chan_send(chan, "channel");
  log_info("Sent....");

  // Later receive the values.
  void *msg;

  chan_recv(chan, &msg);
  log_info("recv1>%s", (char *)msg);

  chan_recv(chan, &msg);
  log_info("recv2>%s", (char *)msg);

  // Clean up channel.
  chan_dispose(chan);
}
