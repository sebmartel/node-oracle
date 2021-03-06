
#ifndef _connection_h_
#define _connection_h_

#include <v8.h>
#include <node.h>
#ifndef WIN32
  #include <unistd.h>
#endif
#include <occi.h>
#include <oro.h>
#include "utils.h"
#include "nodeOracleException.h"
#include "executeBaton.h"

using namespace node;
using namespace v8;

class Connection : ObjectWrap {
public:
  static void Init(Handle<Object> target);
  static Handle<Value> New(const Arguments& args);
  static Handle<Value> Execute(const Arguments& args);
  static Handle<Value> Close(const Arguments& args);
  static Handle<Value> Commit(const Arguments& args);
  static Handle<Value> Rollback(const Arguments& args);
  static Handle<Value> SetAutoCommit(const Arguments& args);
  static Persistent<FunctionTemplate> constructorTemplate;
  static void EIO_Execute(uv_work_t* req);
  static void EIO_AfterExecute(uv_work_t* req, int status);
  static void EIO_Commit(uv_work_t* req);
  static void EIO_AfterCommit(uv_work_t* req, int status);
  static void EIO_Rollback(uv_work_t* req);
  static void EIO_AfterRollback(uv_work_t* req, int status);
  void closeConnection();

  Connection();
  ~Connection();

  void setConnection(oracle::occi::Environment* environment, oracle::occi::Connection* connection);
  oracle::occi::Environment* getEnvironment() { return m_environment; }

private:
  static int SetValuesOnStatement(oracle::occi::Statement* stmt, std::vector<value_t*> &values);
  static void CreateColumnsFromResultSet(oracle::occi::ResultSet* rs, std::vector<column_t*> &columns);
  static row_t* CreateRowFromCurrentResultSetRow(oracle::occi::ResultSet* rs, std::vector<column_t*> &columns);
  static Local<Array> CreateV8ArrayFromRows(ExecuteBaton* baton);
  static Local<Object> CreateV8ObjectFromRow(ExecuteBaton* baton, row_t* currentRow);

  oracle::occi::Connection* m_connection;
  oracle::occi::Environment* m_environment;
  bool m_autoCommit;
};

#endif
