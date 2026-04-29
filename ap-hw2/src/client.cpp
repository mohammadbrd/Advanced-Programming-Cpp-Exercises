#include "client.h"
#include "server.h"

Client :: Client(std::string id, const Server& server):id{id},server{&server}
{
    crypto::generate_key(public_key, private_key);
}
////////////////////////////////////////////////////////////////////////////
std::string Client :: get_id()
{
    return id;
}
////////////////////////////////////////////////////////////////////////////
std::string Client :: get_publickey() const
{
    return public_key;
}
////////////////////////////////////////////////////////////////////////////
double Client :: get_wallet()
{
    Server s = *server;
    return s.get_wallet(id);
}
////////////////////////////////////////////////////////////////////////////
std::string Client :: sign(std::string txt) const
{
    std::string signature = crypto::signMessage(private_key, txt);
    return signature;
}
////////////////////////////////////////////////////////////////////////////
bool Client :: transfer_money(std::string receiver, double value)
{
    std::string sign1{};
    bool i{};
    std::string trx{};
    trx += id;
    trx += '-';
    trx += receiver;
    trx += '-';
    trx += std::to_string(value);
    sign1 = sign(trx);
    Server s = *server;
    i = s.add_pending_trx(trx, sign1);
    if(i)
        return true;
    return 0;
}
////////////////////////////////////////////////////////////////////////////
size_t Client :: generate_nonce()
{
    std::random_device rd;
    std::default_random_engine generator(rd());
    std::uniform_int_distribution<> distribution(0,8585);
    int number = distribution(generator);
    return static_cast<size_t>(number);
}