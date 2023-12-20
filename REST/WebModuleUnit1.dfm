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
      Name = 'zakasnjelePosudbe'
      PathInfo = '/zakasnjelePosudbe'
      OnAction = WebModule1zakasnjelePosudbeAction
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
    end>
  Height = 264
  Width = 427
  object ADOConnection1: TADOConnection
    Connected = True
    ConnectionString = 
      'Provider=Microsoft.ACE.OLEDB.12.0;Data Source=C:\Users\Hrsto\One' +
      'Drive\Radna povr'#353'ina\Projekt ntp\baza.accdb;Persist Security Inf' +
      'o=False'
    LoginPrompt = False
    Mode = cmShareDenyNone
    Provider = 'Microsoft.ACE.OLEDB.12.0'
    Left = 59
    Top = 115
  end
  object ADOQueryKORISNICI: TADOQuery
    Connection = ADOConnection1
    CursorType = ctStatic
    Parameters = <>
    SQL.Strings = (
      'SELECT * FROM korisnici')
    Left = 199
    Top = 24
    object ADOQueryKORISNICIID: TAutoIncField
      FieldName = 'ID'
      ReadOnly = True
    end
    object ADOQueryKORISNICIime: TWideStringField
      FieldName = 'ime'
      Size = 255
    end
    object ADOQueryKORISNICIprezime: TWideStringField
      FieldName = 'prezime'
      Size = 255
    end
    object ADOQueryKORISNICIidKnjige: TIntegerField
      FieldName = 'idKnjige'
    end
    object ADOQueryKORISNICIUkupnoPosudjenoKnjiga: TIntegerField
      DefaultExpression = 'SUM(IIF(knjige.idKorisnik = korisnici.ID, 1, 0))'
      FieldKind = fkCalculated
      FieldName = 'UkupnoPosudjenoKnjiga'
      Calculated = True
    end
  end
  object DataSourceKORISNICI: TDataSource
    DataSet = ADOQueryKORISNICI
    Left = 319
    Top = 24
  end
  object ADOQueryKNJIGE: TADOQuery
    Connection = ADOConnection1
    CursorType = ctStatic
    Parameters = <>
    SQL.Strings = (
      'SELECT * FROM knjige')
    Left = 199
    Top = 120
    object ADOQueryKNJIGEID: TAutoIncField
      FieldName = 'ID'
      ReadOnly = True
    end
    object ADOQueryKNJIGEnaziv: TWideStringField
      FieldName = 'naziv'
      Size = 255
    end
    object ADOQueryKNJIGEpisac: TWideStringField
      FieldName = 'pisac'
      Size = 255
    end
    object ADOQueryKNJIGEdatumPosudivanja: TWideStringField
      FieldName = 'datumPosudivanja'
      Size = 255
    end
    object ADOQueryKNJIGEdatumVracanja: TWideStringField
      FieldName = 'datumVracanja'
      Size = 255
    end
    object ADOQueryKNJIGEidKorisnik: TIntegerField
      FieldName = 'idKorisnik'
    end
    object ADOQueryKNJIGEidLogin: TIntegerField
      FieldName = 'idLogin'
    end
    object ADOQueryKNJIGEIzgledkorice: TBlobField
      FieldName = 'Izgled korice'
    end
  end
  object DataSourceKNJIGE: TDataSource
    DataSet = ADOQueryKNJIGE
    Left = 319
    Top = 128
  end
  object ADOQueryLOG: TADOQuery
    Connection = ADOConnection1
    Parameters = <>
    SQL.Strings = (
      'SELECT * FROM login')
    Left = 192
    Top = 192
  end
  object DataSourceLOG: TDataSource
    DataSet = ADOQueryLOG
    Left = 323
    Top = 200
  end
end
