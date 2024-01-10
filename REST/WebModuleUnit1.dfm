object WebModule1: TWebModule1
  OldCreateOrder = False
  Actions = <
    item
      Default = True
      Name = 'DefaultHandler'
      PathInfo = '/'
      OnAction = WebModule1DefaultHandlerAction
    end
    item
      Name = 'dodavanjeRadnika'
      PathInfo = '/dodavanjeRadnika'
      OnAction = WebModule1dodavanjeRadnikaAction
    end
    item
      MethodType = mtPut
      Name = 'urediRadnika'
      PathInfo = '/urediRadnika'
      OnAction = WebModule1urediRadnikaAction
    end
    item
      MethodType = mtDelete
      Name = 'izbrisiRadnika'
      PathInfo = '/izbrisiRadnika'
      OnAction = WebModule1izbrisiRadnikaAction
    end
    item
      Name = 'LogIn'
      PathInfo = '/LogIn'
      OnAction = WebModule1LogInAction
    end>
  Height = 264
  Width = 427
  object ADOConnection1: TADOConnection
    ConnectionString = 
      'Provider=Microsoft.ACE.OLEDB.12.0;Data Source="C:\Projekt ntp\RE' +
      'ST\bazaREST.accdb";Persist Security Info=False;'
    LoginPrompt = False
    Mode = cmShareDenyNone
    Provider = 'Microsoft.ACE.OLEDB.12.0'
    Left = 59
    Top = 115
  end
  object ADOQueryLOG: TADOQuery
    Connection = ADOConnection1
    Parameters = <>
    SQL.Strings = (
      'SELECT * FROM login')
    Left = 200
    Top = 120
  end
  object DataSourceLOG: TDataSource
    DataSet = ADOQueryLOG
    Left = 323
    Top = 128
  end
end
