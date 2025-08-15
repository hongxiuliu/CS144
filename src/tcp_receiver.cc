#include "tcp_receiver.hh"
#include "debug.hh"

using namespace std;

void TCPReceiver::receive( TCPSenderMessage message )
{
  // Your code here.
  // debug( "unimplemented receive() called" );
  // (void)message;
  if(message.SYN){
    syn=true;
    zero_point=message.seqno;
  }
   if ( message.RST )
    reassembler_.reader().set_error();
  if(!syn) return;
  reassembler_.insert(message.seqno.unwrap(zero_point,reassembler_.writer().bytes_pushed())-1+message.SYN,message.payload,message.FIN);

}

TCPReceiverMessage TCPReceiver::send() const
{
  // Your code here.
  // debug( "unimplemented send() called" );
  // return {};
  TCPReceiverMessage message;
  if(syn){
  message.ackno=Wrap32::wrap(reassembler_.writer().bytes_pushed()+1+reassembler_.writer().is_closed(),zero_point);
  }
  if(reassembler_.writer().has_error()) message.RST=true;
  message.window_size=min(reassembler_.writer().available_capacity(),(uint64_t)(1<<16)-1);
  return message;
}
