class AtlasPh{
  public:
  AtlasPh(Stream &);
  float getPh();
  void setTemp(float t);
  private:
  Stream &_stream;
};

AtlasPh::AtlasPh( Stream &s):_stream(s)
{}

float AtlasPh::getPh()
{
  float ph = -1;
   String reply; reply.reserve(30);
  _stream.print("R\r");
  reply = _stream.readStringUntil(13);
  if ( isdigit(reply[0]) )
  {
    ph = reply.toFloat();
  }

  return ph;
}

void AtlasPh::setTemp(float t)
{
     String reply; reply.reserve(30);
  _stream.print("T,");
  _stream.print(t);
  _stream.print("\r");
  reply = _stream.readStringUntil(13);
 }

