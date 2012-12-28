VERSION 5.00
Begin VB.Form frmMain 
   BorderStyle     =   4  'Fixed ToolWindow
   Caption         =   "ROM"
   ClientHeight    =   5535
   ClientLeft      =   45
   ClientTop       =   285
   ClientWidth     =   7095
   BeginProperty Font 
      Name            =   "Verdana"
      Size            =   8.25
      Charset         =   0
      Weight          =   400
      Underline       =   0   'False
      Italic          =   0   'False
      Strikethrough   =   0   'False
   EndProperty
   LinkTopic       =   "Form1"
   MaxButton       =   0   'False
   MinButton       =   0   'False
   ScaleHeight     =   5535
   ScaleWidth      =   7095
   StartUpPosition =   2  'CenterScreen
   Begin VB.CommandButton cmdTo 
      Caption         =   "To Byte"
      Height          =   375
      Left            =   5880
      TabIndex        =   4
      Top             =   5040
      Width           =   1095
   End
   Begin VB.CommandButton cmdFrom 
      Caption         =   "From Byte"
      Height          =   375
      Left            =   4680
      TabIndex        =   3
      Top             =   5040
      Width           =   1095
   End
   Begin VB.CommandButton cmdWrite 
      Caption         =   "Write"
      Height          =   375
      Left            =   1320
      TabIndex        =   2
      Top             =   5040
      Width           =   1095
   End
   Begin VB.CommandButton cmdRead 
      Caption         =   "Read"
      Height          =   375
      Left            =   120
      TabIndex        =   1
      Top             =   5040
      Width           =   1095
   End
   Begin VB.TextBox txtROM 
      Height          =   4815
      Left            =   120
      MultiLine       =   -1  'True
      ScrollBars      =   2  'Vertical
      TabIndex        =   0
      Top             =   120
      Width           =   6855
   End
End
Attribute VB_Name = "frmMain"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
Option Explicit

Private Function FromByte(ByVal Bin As Byte) As String
    Dim sRet As String
    Do Until Bin = 0
        If (Bin Mod 2) Then
            sRet = "1" & sRet
        Else
            sRet = "0" & sRet
        End If
        Bin = Bin \ 2
    Loop
    If sRet = vbNullString Then
        FromByte = "00000000"
    Else
        Do While Len(sRet) < 8
            sRet = "0" & sRet
        Loop
        FromByte = sRet
    End If
End Function

Private Function ToByte(ByVal Data As String) As Byte
    Dim b As Byte
    Dim i As Integer
    Dim e As Integer
    b = 0
    e = 7
    For i = 1 To Len(Data)
        If Mid$(Data, i, 1) = "1" Then
            b = b + (2 ^ e)
        End If
        e = e - 1
    Next
    ToByte = b
End Function

Private Sub cmdFrom_Click()
    Dim s As String
    s = Trim$(InputBox$("Byte:"))
    MsgBox FromByte(Val(s))
End Sub

Private Sub cmdRead_Click()
    Dim iFile As Integer
    Dim b As Byte
    txtROM.Text = vbNullString
    If FileLen(App.Path & "\rom.bin") Then
        iFile = FreeFile
        Open App.Path & "\rom.bin" For Binary Access Read As #iFile
        Do While Not EOF(iFile)
            Get #iFile, , b
            txtROM.Text = txtROM.Text & FromByte(b) & vbCrLf
        Loop
        Close #iFile
    End If
End Sub

Private Sub cmdTo_Click()
    Dim s As String
    s = Trim$(InputBox$("Binary:"))
    MsgBox "DEC: " & ToByte(s) & vbCrLf & "HEX: " & Hex$(ToByte(s))
End Sub

Private Sub cmdWrite_Click()
    Dim iFile As Integer
    Dim s() As String
    Dim i As Integer
    s() = Split(txtROM.Text, vbCrLf)
    iFile = FreeFile
    Open App.Path & "\rom.bin" For Binary Access Write As #iFile
    For i = 0 To UBound(s())
        If s(i) <> vbNullString Then
            Put #iFile, , ToByte(s(i))
        End If
    Next
    Put #iFile, , &HFF 'HALT
    Close #iFile
End Sub
