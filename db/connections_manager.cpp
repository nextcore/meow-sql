#include "connections_manager.h"
#include "connection.h"

namespace meow {
namespace db {

ConnectionsManager::ConnectionsManager()
    :QObject(),
     Entity(),
     _connections(),
     _activeEntity()
{

}

ConnectionsManager::~ConnectionsManager()
{
    qDeleteAll(_connections);
}

ConnectionPtr ConnectionsManager::openDBConnection(db::ConnectionParameters & params)
{
    ConnectionPtr connection = params.createConnection();

    connection->setActive(true);

    SessionEntity * newSession = new SessionEntity(connection, this);

    _connections.push_back(newSession);
    _activeSession = newSession;

    emit connectionOpened(newSession);

    return connection;
}

int ConnectionsManager::childCount() // override
{
    return _connections.size();
}

SessionEntity * ConnectionsManager::child(int row) // override
{
    return _connections.value(row); // returns null if out of bounds
}

int ConnectionsManager::indexOf(SessionEntity * session) const
{
    return _connections.indexOf(session);
}

Connection * ConnectionsManager::activeConnection() const
{
    if (_activeSession) {
        return _activeSession->connection();
    }
    return nullptr;
}

void ConnectionsManager::setActiveEntity(Entity * activeEntity)
{
    bool changed = _activeEntity.setCurrentEntity(activeEntity);
    if (changed) {
        // TODO: Session changed

        if (_activeEntity.databaseChanged()) {
            Connection * connection = activeConnection();
            if (connection) {
                QString dbName = databaseName(activeEntity);
                connection->setDatabase(dbName);
            }
        }

        emit activeEntityChanged(activeEntity);
    }
}

} // namespace db
} // namespace meow
