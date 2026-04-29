#include "server.h"
#include "client.h"

Server :: Server():clients{}
{

}
////////////////////////////////////////////////////////////////////////////
std::shared_ptr<Client> Server :: add_client(std::string id)
{
    std::string idd = id;
    std::random_device rd;
    std::default_random_engine generator(rd());
    std::uniform_int_distribution<> distribution(1000,9999);
    for(auto i = clients.begin();i != clients.end();i++)
    {
        if(i->first->get_id() == id)
        {
            int number = distribution(generator);
            idd += std::to_string(number);
            break;
        }
    }
    Client a(idd, *this);
    std::shared_ptr<Client> b = std::make_shared<Client>(a);
    clients.insert({b,5});
    return b;
}
////////////////////////////////////////////////////////////////////////////
std::shared_ptr<Client> Server :: get_client(std::string id) const
{
    std::shared_ptr<Client> j{nullptr};
    for(auto i = clients.begin();i != clients.end();i++)
        if(i->first->get_id() == id)
            j = i->first;
    return j;
}
////////////////////////////////////////////////////////////////////////////
double Server :: get_wallet(std::string id)
{
    double j{0};
    for(auto i = clients.begin();i != clients.end();i++)
        if(i->first->get_id() == id)
            j = i->second;
    return j;
}
////////////////////////////////////////////////////////////////////////////
bool Server :: parse_trx(std::string trx, std::string &sender, std::string &receiver, double &value)
{
    size_t find1 = trx.find('-');
    size_t find2 = trx.find('-', find1 + 1);
    if(find1 == std::string::npos or find2 == std::string::npos)
        throw std::runtime_error("We cannt find (-)");
    sender = trx.substr(0, find1);
    receiver = trx.substr(find1 + 1, find2 - find1 - 1);
    value = std::stod(trx.substr(find2 + 1));
    return 0;
}
////////////////////////////////////////////////////////////////////////////
bool Server :: add_pending_trx(std::string trx, std::string signature)
{
    std::string sender{}, receiver{};
    std::shared_ptr<Client>  temp1{}, temp2{};
    double value{}, value_sender{};
    parse_trx(trx, sender, receiver, value);
    temp1 = get_client(sender);
    temp2 = get_client(receiver);
    value_sender = get_wallet(sender);
    bool authentic = crypto::verifySignature(temp1->get_publickey(), trx, signature);
    if(authentic && temp1 != nullptr && temp2 != nullptr && value_sender >= value)
    {
        pending_trxs.push_back(trx);
        return true;
    }      
    return 0;
}
////////////////////////////////////////////////////////////////////////////
size_t Server :: mine()
{
    size_t size{pending_trxs.size()};
    std::string mempool{}, sender{}, receiver{};
    std::shared_ptr<Client>  temp1{}, temp2{};
    size_t nonce{};
    double value{};
    for(auto i: pending_trxs)
        mempool += i;
    while(1)
    {
        int i{0};
        parse_trx(pending_trxs[i], sender, receiver, value);
        temp1 = get_client(sender);
        nonce = temp1->generate_nonce();
        std::string hash = crypto::sha256(mempool + std::to_string(nonce));
        if(hash.substr(0, 10).find("000") != std::string::npos)
        {
            std::cout<<sender<<std::endl;
            clients[temp1] += 6.25;
            break;
        }   
        i++;
        if(i == size)
            i = 0;
    }
    for(auto i:pending_trxs)
    {
        parse_trx(i, sender, receiver, value);
        temp1 = get_client(sender);
        temp2 = get_client(receiver);
        clients[temp1] -= value;
        clients[temp2] += value;
    }
    pending_trxs.clear();
    return nonce;
}