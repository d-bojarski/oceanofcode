#include "ai.h"
#include "messagemanager.h"

int main()
{
    MessageManager messageManager;
    AI ai(&messageManager);
    ai.start();
}