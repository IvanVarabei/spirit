object Form4: TForm4
  Left = 674
  Top = 129
  Width = 388
  Height = 456
  Caption = 'Menu'
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'Tahoma'
  Font.Style = []
  OldCreateOrder = False
  PixelsPerInch = 96
  TextHeight = 13
  object rg1: TRadioGroup
    Left = 40
    Top = 16
    Width = 289
    Height = 321
    Caption = 'Choose form:'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -16
    Font.Name = 'Tahoma'
    Font.Style = []
    Items.Strings = (
      'form with image'
      'form with shape'
      'form with paintbox')
    ParentFont = False
    TabOrder = 0
    OnClick = rg1Click
  end
  object btn1: TButton
    Left = 120
    Top = 368
    Width = 145
    Height = 25
    Caption = 'Exit'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -16
    Font.Name = 'Tahoma'
    Font.Style = []
    ParentFont = False
    TabOrder = 1
    OnClick = btn1Click
  end
end
