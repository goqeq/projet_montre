import 'package:flutter/cupertino.dart';
import 'package:flutter/material.dart';

class EventPage extends StatelessWidget {
  const EventPage({super.key});

  @override
  Widget build(BuildContext context) {
    return Scaffold(
      appBar: AppBar(

        title: const Center(
          child: Text("Planning"),
        ),
      ),
      body: Center(
        child: ListView(
            children: const [
              Card(
                child: ListTile(
                  leading: FlutterLogo(size: 56.0),
                  title: Text('première carte'),
                  subtitle: Text("ceci est une description"),
                  trailing: Icon(Icons.account_circle),
                ),
              )
            ]
        ),
      ),
    );
  }
}