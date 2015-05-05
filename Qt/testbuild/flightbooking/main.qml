import QtQuick 2.4
import QtQuick.Controls 1.3
import QtQuick.Window 2.2
import QtQuick.Dialogs 1.2
import QtQuick 2.1
import Enginio 1.0
import QtQuick.Controls 1.0
import QtQuick.Layouts 1.0
import com.myself 1.0
//----------------------------------
import QtMultimedia 5.0
import QtTest 1.1
ApplicationWindow {
    title: qsTr("Hoa's Global Travel Agency")
    width: 800
    height: 600
    color: "#b5a7e6"
    visible: true
//----------------------------------
    // An instance of a class.
    // Every class needs this.
    Admin{
        id: admin
    }
    Login{
        id: login
    }
//----------------------------------
    // This is used for popup boxes.
    MessageDialog {
        id: messageDialog
        title: qsTr("May I have your attention, please?")

        function show(caption) {
            messageDialog.text = caption;
            messageDialog.open();
        }
    }
//----------------------------------
    // This can be left empty or we can add menu items.
    menuBar: MenuBar {

    }
//----------------------------------
    //This is the MainForm that loads on initial load of the program.
    // Will also be used after a user logs out.
    MainForm {
        id: mainForm1
        anchors.rightMargin: 0
        anchors.bottomMargin: 0
        anchors.leftMargin: 0
        anchors.topMargin: 0
        anchors.fill: parent

        //Loads the background image for the welcome screen.
        Image {
            id: background
            width: 800
            height: 600
            sourceSize.height: 800
            sourceSize.width: 600
            fillMode: Image.Stretch
            source: "images/bckgrnd.jpg"
        }
        //The register button.
        //Takes you to the register form for users to create an account.
        Button {
            id: register
            x: 358
            y: 392
            text: qsTr("Register")
            activeFocusOnPress: false
            checkable: false
            tooltip: "Click to register"
            onClicked: {
                mainForm1.visible = false
                userCreateAccount.visible = true
            }
        }

        Button {
            id: showAdmin
            x: 45
            y: 113
            text: qsTr("Show Admin")
            onClicked: {
                mainForm1.visible = false
                adminForm.visible = true
            }
        }
        //Login button.
        // This code section will get slightly big as it does the initial form loads.
        Button {
            id: loginButton
            x: 366
            y: 252
            text: qsTr("Login")
            //onClicked: messageDialog.show(admin.displayMessage())
            onClicked:{
                mainForm1.visible = false
                //messageDialog.show(login.validateLogin(userName.text, password.text))
                var result = login.validateLogin(userName.text, password.text)
                // Loads the form if no account found for a user to create an acoount.
                if(result == "userCreateAccount"){
                    userCreateAccount.visible = true
                    messageDialog.show("No account found, please create an account.")
                }
                if(result == "customer"){
                    customerForm.visible = true
                }
                if(result == "admin"){
                    adminForm.visible = true
                }
                if(result == "flightmanager"){
                    flightForm.visible = true
                }
                if(result == "bookingmanager"){
                    bookingForm.visible = true
                }
                if(result == "servicemanager"){
                    serviceForm.visible = true
                }
            }
        }
        //Text area to enter username if already registered.
        TextField {
            id: userName
            x: 350
            y: 177
            font.italic: true
            opacity: 1
            placeholderText: qsTr("Username")
        }
        //Text area to enter password if already registered.
        TextField {
            id: password
            x: 350
            y: 210
            echoMode: 2
            inputMask: qsTr("")
            font.italic: true
            placeholderText: qsTr("Password")
        }
    }
//----------------------------------
    //This form is for customers to create their own accounts.
    MainForm{
        id: userCreateAccount
        visible: false
        anchors.rightMargin: 0
        anchors.bottomMargin: 0
        anchors.leftMargin: 0
        anchors.topMargin: 0
        anchors.fill: parent
        //visible: false
        Image {
            id: background2
            width: 800
            height: 600
            sourceSize.height: 480
            sourceSize.width: 640
            fillMode: Image.Stretch
            source: "images/bckgrnd.jpg"
        }
        ColumnLayout {
            x: 210
            y: 64
            width: 380
            height: 147
            anchors.margins: 3
            spacing: 3

            TextField {
                id: userName3
                Layout.fillWidth: true
                placeholderText: "Username"
            }

            TextField {
                id: password2
                Layout.fillWidth: true
                placeholderText: "Password"
                echoMode: 2
                inputMask: qsTr("")
                font.italic: true
            }

            TextField {
                id: userFirstName
                Layout.fillWidth: true
                placeholderText: "First name"
            }

            TextField {
                id: userLastName
                Layout.fillWidth: true
                placeholderText: "Last name"
            }


            TextField {
                id: userEmail
                Layout.fillWidth: true
                placeholderText: "Email"
            }
        }
        Button {
            id: back
            x: 18
            y: 17
            text: qsTr("Back")
            onClicked: {
                mainForm1.visible = true
                userCreateAccount.visible = false
            }
        }
        Button {
            id: register2
            x: 357
            y: 249
            text: qsTr("Register")
            tooltip: "Click to register"
        }
    }
//----------------------------------
    //This form is for the Administrator to add new users.
    MainForm{
        id: adminCreateUser
        anchors.rightMargin: 0
        anchors.bottomMargin: 0
        anchors.leftMargin: 0
        anchors.topMargin: 0
        anchors.fill: parent
        visible: false
        Image {
            id: background3
            x: 0
            y: 0
            width: 800
            height: 600
            sourceSize.height: 480
            sourceSize.width: 640
            fillMode: Image.Stretch
            source: "images/bckgrnd.jpg"
        }
        ColumnLayout {
            x: 210
            y: 63
            width: 380
            height: 147
            anchors.margins: 3
            spacing: 3

            TextField {
                id: userName2
                Layout.fillWidth: true
                placeholderText: "Username"
            }

            TextField {
                id: password3
                Layout.fillWidth: true
                placeholderText: "Password"
                echoMode: 2
                inputMask: qsTr("")
                font.italic: true
            }

            TextField {
                id: userFirstName2
                Layout.fillWidth: true
                placeholderText: "First name"
            }

            TextField {
                id: userLastName2
                Layout.fillWidth: true
                placeholderText: "Last name"
            }

            TextField {
                id: userEmail2
                Layout.fillWidth: true
                placeholderText: "Email"
            }

            TextField{
                id: role
                Layout.fillWidth: true
                placeholderText: "Account type"
            }
        }
        Button {
            id: back2
            x: 18
            y: 17
            text: qsTr("Back")
            onClicked: {
                mainForm1.visible = true
                adminCreateUser.visible = false
            }
        }
        Button {
            id: register3
            x: 357
            y: 249
            text: qsTr("Register")
            tooltip: "Click to register"
        }
    }
//----------------------------------
    // The administrators form
    MainForm{
        id: adminForm
        anchors.rightMargin: 0
        anchors.bottomMargin: 0
        anchors.leftMargin: 0
        anchors.topMargin: 0
        anchors.fill: parent
        visible: false

        Image {
            id: adminBackground
            x: 0
            y: 0
            width: 800
            height: 600
            clip: false
            visible: true
            sourceSize.height: 480
            sourceSize.width: 640
            fillMode: Image.Stretch
            source: "images/bckgrnd.jpg"
        }

        Button {
            id: flightManagement
            x: 228
            y: 51
            text: qsTr("Flight Management")
            onClicked: {
                adminForm.visible = false
                flightForm.visible = true
            }
        }

        Button {
            id: profileManagement
            x: 420
            y: 51
            text: qsTr("Profile Management")
            onClicked: {
                adminForm.visible = false
                profileForm.visible = true
            }
        }

        Button {
            id: serviceManagement
            x: 616
            y: 51
            text: qsTr("Service Management")
            onClicked: {
                adminForm.visible = false
               serviceForm.visible = true
            }
        }

        Button {
            id: backToMain
            x: 8
            y: 566
            text: qsTr("Back")
            onClicked: {
                adminForm.visible = false
                mainForm1.visible = true
            }
        }
        Button {
            id: bookingManagement
            x: 8
            y: 51
            text: qsTr("Booking Management")
            visible: true
            onClicked: {
                adminForm.visible = false
                bookingForm.visible = true
            }
        }

        Button {
            id: generateReports
            x: 8
            y: 109
            text: qsTr("Generate Reports")
        }
    }
//----------------------------------
    // Booking managers form.
    MainForm {
        id: bookingForm
        anchors.rightMargin: 0
        anchors.bottomMargin: 0
        anchors.leftMargin: 0
        anchors.topMargin: 0
        anchors.fill: parent
        visible: false

        Image {
            id: bookingBackground
            x: 0
            y: 0
            width: 800
            height: 600
            clip: false
            visible: true
            sourceSize.height: 480
            sourceSize.width: 640
            fillMode: Image.Stretch
            source: "images/bckgrnd.jpg"
        }

        Button {
            id: backToprevious
            x: 15
            y: 18
            text: qsTr("Back")
            onClicked: {
                bookingForm.visible = false
                adminForm.visible = true
            }
        }
    }
//----------------------------------
    // Flight managers form.
    MainForm {
        id: flightForm
        anchors.rightMargin: 0
        anchors.bottomMargin: 0
        anchors.leftMargin: 0
        anchors.topMargin: 0
        anchors.fill: parent
        visible: false

        Image {
            id: flightBackground
            x: 0
            y: 0
            width: 800
            height: 600
            clip: false
            visible: true
            sourceSize.height: 480
            sourceSize.width: 640
            fillMode: Image.Stretch
            source: "images/bckgrnd.jpg"
        }
    }
//----------------------------------
    // Profile managers form.
    MainForm {
        id: profileForm
        anchors.rightMargin: 0
        anchors.bottomMargin: 0
        anchors.leftMargin: 0
        anchors.topMargin: 0
        anchors.fill: parent
        visible: false

        Image {
            id: profileBackground
            x: 0
            y: 0
            width: 800
            height: 600
            clip: false
            visible: true
            sourceSize.height: 480
            sourceSize.width: 640
            fillMode: Image.Stretch
            source: "images/bckgrnd.jpg"
        }
    }
    //----------------------------------
    // Service managers form.
    MainForm {
        id: serviceForm
        anchors.rightMargin: 0
        anchors.bottomMargin: 0
        anchors.leftMargin: 0
        anchors.topMargin: 0
        anchors.fill: parent
        visible: false

        Image {
            id: serviceBackground
            x: 0
            y: 0
            width: 800
            height: 600
            clip: false
            visible: true
            sourceSize.height: 480
            sourceSize.width: 640
            fillMode: Image.Stretch
            source: "images/bckgrnd.jpg"
        }

    }
    //----------------------------------
    // Customers form.
    MainForm {
        id: customerForm
        anchors.rightMargin: 0
        anchors.bottomMargin: 0
        anchors.leftMargin: 0
        anchors.topMargin: 0
        anchors.fill: parent
        visible: false

        Image {
            id: userBackground
            x: 0
            y: 0
            width: 800
            height: 600
            clip: false
            visible: true
            sourceSize.height: 480
            sourceSize.width: 640
            fillMode: Image.Stretch
            source: "images/bckgrnd.jpg"
        }


    }
//----------------------------------
}













