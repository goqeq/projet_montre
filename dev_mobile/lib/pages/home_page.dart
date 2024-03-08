import 'package:flutter/material.dart';
import 'event_page.dart';

class HomePage extends StatelessWidget {
  const HomePage({super.key});

  @override
  Widget build(BuildContext context) {
    return Scaffold(

      backgroundColor: Colors.black45,

      appBar: AppBar(

        backgroundColor: Colors.white12,

        title: const Center(
          child: Text(
            "Montre app v0",
            style: TextStyle(
              fontFamily: 'Poppins',
              color: Colors.white,
            ),
          ),
        ),
      ),

      body: Center(
          child: Column(
            mainAxisAlignment: MainAxisAlignment.center,

            children: [
              const Text(
                "Bienvenue",
                style: TextStyle(
                    fontSize: 24,
                    fontFamily: 'Poppins',
                    color: Colors.white
                ),
              ),
              const Text("salon de ma chambre",
                style: TextStyle(
                  fontSize: 15,
                  color: Colors.grey,
                ),
                textAlign: TextAlign.center,
              ),
              const Padding(padding: EdgeInsets.only(top:30)),
              ElevatedButton(
                style: const ButtonStyle(
                  padding: MaterialStatePropertyAll(EdgeInsets.all(15)),
                  backgroundColor: MaterialStatePropertyAll(Colors.blue),
                ),
                child: const Text("Entrez dans L'application",
                  style: TextStyle(
                    fontSize: 18,
                    color: Colors.white,
                  ),
                ),
                onPressed: () {
                  Navigator.push(
                    context,
                    PageRouteBuilder(
                      pageBuilder: (_, __, ___) => const EventPage(),
                    ),
                  );
                },
              ),
            ],
          )
      ),
    );
  }
}