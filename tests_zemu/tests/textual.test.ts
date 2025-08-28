import Zemu, { ClickNavigation, TouchNavigation, isTouchDevice } from '@zondax/zemu'
// @ts-ignore
import CreataApp from 'ledger-creatachain-js'
// import  CreataApp  from './../../js/src'

import { defaultOptions, DEVICE_MODELS, tx_sign_textual, TEXTUAL_TX } from './common'
// @ts-ignore
import secp256k1 from 'secp256k1/elliptic'
// @ts-ignore
import crypto from 'crypto'
import { ButtonKind, IButton, SwipeDirection } from '@zondax/zemu/dist/types'

jest.setTimeout(90000)

// Textual mode is not available for NanoS
const TEXTUAL_MODELS = DEVICE_MODELS.filter(m => m.name !== 'nanos')

describe('Textual', function () {
  // eslint-disable-next-line jest/expect-expect
  test.concurrent.each(TEXTUAL_MODELS)('can start and stop container', async function (m) {
    const sim = new Zemu(m.path)
    try {
      await sim.start({ ...defaultOptions, model: m.name })
    } finally {
      await sim.close()
    }
  })

  test.concurrent.each(TEXTUAL_MODELS)('sign basic textual', async function (m) {
    const sim = new Zemu(m.path)
    try {
      await sim.start({ ...defaultOptions, model: m.name })
      const app = new CreataApp(sim.getTransport())

      const path = "m/44'/118'/0'/0/0"
      const tx = Buffer.from(tx_sign_textual, 'hex')
      const hrp = 'creata'

      // get address / publickey
      const respPk = await app.getAddressAndPubKey(path, hrp)
      expect(respPk).toHaveProperty('compressed_pk')
      expect(respPk).toHaveProperty('bech32_address')
      console.log(respPk)

      // do not wait here..
      const signatureRequest = app.sign(path, tx, hrp, TEXTUAL_TX)

      // Wait until we are not in the main menu
      await sim.waitUntilScreenIsNot(sim.getMainMenuSnapshot())
      await sim.compareSnapshotsAndApprove('.', `${m.prefix.toLowerCase()}-textual-sign_basic`)

      const resp = await signatureRequest
      console.log(resp)

      expect(resp).toHaveProperty('signature')

      // Now verify the signature
      const hash = crypto.createHash('sha256')
      const msgHash = Uint8Array.from(hash.update(tx).digest())

      const signatureDER = resp.signature
      const signature = secp256k1.signatureImport(Uint8Array.from(signatureDER))

      const pk = Uint8Array.from(respPk.compressed_pk)

      const signatureOk = secp256k1.ecdsaVerify(signature, msgHash, pk)
      expect(signatureOk).toEqual(true)
    } finally {
      await sim.close()
    }
  })

  test.concurrent.each(TEXTUAL_MODELS)('sign basic textual expert', async function (m) {
    const sim = new Zemu(m.path)
    try {
      await sim.start({ ...defaultOptions, model: m.name })
      const app = new CreataApp(sim.getTransport())

      // Change to expert mode so we can skip fields
      await sim.toggleExpertMode()

      const path = "m/44'/118'/0'/0/0"
      const tx = Buffer.from(tx_sign_textual, 'hex')
      const hrp = 'creata'

      // get address / publickey
      const respPk = await app.getAddressAndPubKey(path, hrp)
      expect(respPk).toHaveProperty('compressed_pk')
      expect(respPk).toHaveProperty('bech32_address')
      console.log(respPk)

      // do not wait here..
      const signatureRequest = app.sign(path, tx, hrp, TEXTUAL_TX)

      // Wait until we are not in the main menu
      await sim.waitUntilScreenIsNot(sim.getMainMenuSnapshot())
      await sim.compareSnapshotsAndApprove('.', `${m.prefix.toLowerCase()}-textual-sign_basic_expert`)

      const resp = await signatureRequest
      console.log(resp)

      expect(resp).toHaveProperty('signature')

      // Now verify the signature
      const hash = crypto.createHash('sha256')
      const msgHash = Uint8Array.from(hash.update(tx).digest())

      const signatureDER = resp.signature
      const signature = secp256k1.signatureImport(Uint8Array.from(signatureDER))

      const pk = Uint8Array.from(respPk.compressed_pk)

      const signatureOk = secp256k1.ecdsaVerify(signature, msgHash, pk)
      expect(signatureOk).toEqual(true)
    } finally {
      await sim.close()
    }
  })

})
